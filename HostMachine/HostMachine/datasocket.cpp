#include "datasocket.h"
#include <QHostAddress>
#include <QFileInfo>
#include <QApplication>
#include <QMessageBox>
#include "scopeguard.h"
#include "common.h"
#include "globalfun.h"
#include "..\HostMachineService\datasocket.h"

static const char *c_sDataSocket = "DataSocket";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DataSocket", "网络应用软件");
static const char *c_sNetConnectError = QT_TRANSLATE_NOOP("DataSocket", "无法连接服务器，请检查网络连接！");
static const char *c_sOpenFileError = QT_TRANSLATE_NOOP("DataSocket", "只读方式打开文件<%0>失败！");

CDataSocket::CDataSocket(QObject *parent)
    : QTcpSocket(parent)
{
    connect(this, SIGNAL(siglogRecord(QString)), parent, SLOT(slotLogRecord(QString)));
}

CDataSocket::~CDataSocket()
{

}

void CDataSocket::slotImport()
{
    if (state() != QAbstractSocket::ConnectedState)
    {
        connectToHost(QHostAddress(sIPAddr), c_uDataPort);
        if (!waitForConnected())
        {
            QMessageBox::information(nullptr, qApp->translate(c_sDataSocket, c_sTitle),
                qApp->translate(c_sDataSocket, c_sNetConnectError));
            return;
        }
    }

    foreach(QString sFileName, importFileList)
    {
        QFile file;
        file.setFileName(sFileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QString sInfo = QString(qApp->translate(c_sDataSocket, c_sOpenFileError)).arg(sFileName);
            emit siglogRecord(sInfo);
            continue;
        }

        QFileInfo fileInfo = sFileName;
        qint64 fileSize = fileInfo.size();
        QString sHeader = QString("%0##%1##%2").arg(areano).arg(fileInfo.fileName()).arg(fileSize);
        qint64 len = write(sHeader.toLocal8Bit());
        if (len == -1)
            return;
        waitForReadyRead();

        SCOPE_EXIT { file.close(); };

        emit importStart(areano, fileInfo.fileName(), 0, fileSize);
        qint64 bufferLen = 0;
        do
        {
            char buffer[c_bufferSize] = {0};
            qint64 len = file.read(buffer, sizeof(buffer));
            len = write(buffer, len);
            waitForBytesWritten();
            bufferLen += len;
            if (bufferLen < fileSize)
                emit importUpdate(areano, fileInfo.fileName(), bufferLen, fileSize);
            else
                break;
        } while (true);

        waitForReadyRead();

        emit importCompleted(areano, fileInfo.fileName(), bufferLen, fileSize);
    }
}

void CDataSocket::readyRead()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_5);

    if (bytesAvailable() < sizeof(qint32))
        return;

    QByteArray buf = readAll();
    if (QString(buf) == "Completed!")
        return;

    respondExport(buf);
}

void CDataSocket::respondExport(QByteArray buf)
{
    qint64 len = m_file.write(buf);
    m_bufferSize += len;

    bool bComplete = false;
    if (m_bufferSize >= m_fileSize)
        bComplete = true;

    if(!bComplete)
    {
        QFileInfo fileInfo = m_file.fileName();
        emit exportUpdate(areano, fileInfo.fileName(), m_bufferSize, m_fileSize);
    }
    else
    {
        m_file.close();
        write("Completed!");

        QFileInfo fileInfo = m_file.fileName();
        emit exportCompleted(areano, fileInfo.fileName(), m_bufferSize, m_fileSize);

        m_bufferSize = 0;
    }
}

void CDataSocket::preExport(qint32 areaNo, QString filePath, qint64 fileSize)
{
    areano = areaNo;
    m_file.setFileName(filePath);
    m_file.open(QIODevice::WriteOnly);

    m_fileSize = fileSize;
    m_bufferSize = 0;

    QFileInfo fileInfo = m_file.fileName();
    emit exportStart(areano, fileInfo.fileName(), 0, m_fileSize);
}