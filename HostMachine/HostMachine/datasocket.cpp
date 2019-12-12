#include "datasocket.h"
#include <QHostAddress>
#include <QFileInfo>
#include <QApplication>
#include <QMessageBox>
#include "common.h"
#include "globalfun.h"
#include "datasocket.h"
#include "taskcommon.h"

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

    QFileInfo fileInfo = m_file.fileName();
    QString fileName = fileInfo.fileName();

    qint64 bufferLen = 0;
    int nIndex = 0;
    do
    {
        char buffer[c_bufferSize] = {0};
        qint64 len = m_file.read(buffer, sizeof(buffer));
        len = write(buffer, len);
        if (nIndex % 10 == 0)
            waitForBytesWritten();
        bufferLen += len;
        if (bufferLen < m_fileSize)
            emit importUpdate(areano, fileName, bufferLen, m_fileSize);
        else
            break;

        nIndex ++;
    } while (true);

    m_file.close();

    emit importCompleted(areano, fileName, bufferLen, m_fileSize);
}

void CDataSocket::readyRead()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_5);

    if (bytesAvailable() < sizeof(qint32))
        return;

    QByteArray buf = readAll();
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

bool CDataSocket::preImport(qint32 areaNo, QString filePath)
{
    areano = areaNo;
    m_bufferSize = 0;
    
    m_file.setFileName(filePath);
    if (!m_file.open(QIODevice::ReadOnly))
    {
        QString sInfo = QString(qApp->translate(c_sDataSocket, c_sOpenFileError)).arg(filePath);
        emit siglogRecord(sInfo);
        return false;
    }

    QFileInfo fileInfo = filePath;
    m_fileSize = fileInfo.size();

    emit importStart(areano, fileInfo.fileName(), 0, m_fileSize);

    return true;
}
