#include "datasocket.h"
#include <QHostAddress>
#include <QFileInfo>
#include <QApplication>
#include <QMessageBox>
#include "scopeguard.h"
#include "common.h"
#include "globalfun.h"
#include "QThread"

static const char *c_sDataSocket = "DataSocket";
static const char *c_sTitle = QT_TRANSLATE_NOOP("DataSocket", "网络应用软件");
static const char *c_sNetConnectError = QT_TRANSLATE_NOOP("DataSocket", "无法连接服务器，请检查网络连接！");

DataSocket::DataSocket(QObject *parent)
    : QTcpSocket(parent)
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
        qint64 len = write(sHeader.toUtf8());
        waitForBytesWritten();
        if (len == -1)
            return;
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
    }

    emit importCompleted();
}
