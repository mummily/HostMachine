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

DataSocket::DataSocket(QObject *parent)
    : QTcpSocket(parent), m_bStart(true), m_fileSize(0), m_bufferSize(0)
{

}

DataSocket::~DataSocket()
{

}

void DataSocket::slotImport()
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
#pragma message("DataSocket::slotImport 日志记录")
            continue;

        QFileInfo fileInfo = sFileName;
        qint64 fileSize = fileInfo.size();
        QString sHeader = QString("%0##%1##%2").arg(areano).arg(fileInfo.fileName()).arg(fileSize);
        qint64 len = write(sHeader.toLocal8Bit());
        if (len == -1)
            return;
        waitForReadyRead();

        SCOPE_EXIT([&]{ file.close(); });

        qint64 bufferLen = 0;
        do
        {
            char buffer[c_bufferSize] = {0};
            qint64 len = file.read(buffer, sizeof(buffer));
            len = write(buffer, len);
            bufferLen += len;

            emit updateProcess(sFileName, bufferLen, fileSize);
        } while (bufferLen != fileSize);

        waitForReadyRead();

        emit importCompleted();
    }
}

void DataSocket::readyRead()
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

void DataSocket::respondExport(QByteArray buf)
{
    if (m_bStart)
    {
        m_bStart = false;

        QString sBuf = QString::fromLocal8Bit(buf);
        int areNo = sBuf.section("##", 0, 0).toInt();
        QString fileName = sBuf.section("##", 1, 1);
        QString filePath = QString("%0/%1_%2").arg(exportFilePath).arg(areNo).arg(fileName);

        m_file.setFileName(filePath);
        m_file.open(QIODevice::WriteOnly);

        m_fileSize = sBuf.section("##", 2, 2).toFloat();

        write("Completed!");
    }
    else
    {
        qint64 len = m_file.write(buf);
        m_bufferSize += len;

        emit updateProcess(m_file.fileName(), m_bufferSize, m_fileSize);

        if (m_bufferSize >= m_fileSize)
        {
            m_file.close();
            m_bStart = true;
            m_bufferSize = 0;

            write("Completed!");

            emit exportCompleted();
        }
    }
}
