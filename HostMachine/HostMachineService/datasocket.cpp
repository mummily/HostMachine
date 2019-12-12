#include "datasocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"
#include <QApplication>
#include "QThread"
#include <QDir>
#include <QFile>
#include "..\HostMachine\taskcommon.h"

DataSocket::DataSocket(QObject *parent)
    : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnect()), this, SLOT(deleteLater()));

    initData();
}

DataSocket::~DataSocket()
{
}

void DataSocket::readClient()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_5);

    if (bytesAvailable() < sizeof(qint32))
        return;

    QByteArray buf = readAll();
    respondImport(buf);
}

void DataSocket::respondImport(QByteArray buf)
{
    qint64 len = m_file.write(buf);
    m_blockSize += len;

    if (m_blockSize >= m_fileSize)
    {
        m_file.close();
        m_blockSize = 0;
    }
}

void DataSocket::slotExport()
{
    QString fileFullPath = QString("%0/%1/%2").arg(qApp->applicationDirPath()).arg(areaNo).arg(sFileName);
    QFileInfo fileInfo = fileFullPath;
    fileSize = qMin(fileSize, fileInfo.size() - startPos);

    QFile file;
    file.setFileName(fileFullPath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    file.seek(startPos);

    qint64 bufferLen = 0;
    while (bufferLen < fileSize)
    {
        char buffer[4 * 1024] = {0};
        qint64 len = file.read(buffer, sizeof(buffer));
        len = write(buffer, len);
        if (len < 0)
            break;
        waitForBytesWritten();
        bufferLen += len;
    }
    
    file.close();
}

void DataSocket::initData()
{
    m_blockSize = 0;
    m_fileSize = 0;
    m_bStart = true;
}

void DataSocket::preImport(qint32 areaNo, QString fileName, qint64 fileSize)
{
    initData();

    QString filePath = QString("%0/%1/").arg(qApp->applicationDirPath()).arg(areaNo);
    QDir().mkdir(filePath);
    filePath += fileName;

    m_file.setFileName(filePath);
    m_file.open(QIODevice::WriteOnly);

    m_fileSize = fileSize;
}
