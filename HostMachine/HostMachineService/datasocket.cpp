#include "datasocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"
#include <QApplication>
#include "QThread"
#include <QDir>
#include "common.h"
#include <QFile>
#include "..\include\scopeguard.h"

const QString c_sImportHead= "{2585E781-1C60-416E-9A18-CC7ACD2522AF}";
const QString c_sExportHead= "{FFEE539A-6E91-4461-AD05-8B5F21CAF18D}";

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
    if (QString(buf) == "Completed!")
        return;

    respondImport(buf);
}

void DataSocket::respondImport(QByteArray buf)
{
    if (m_bStart)
    {
        m_bStart = false;

        QString sBuf = QString::fromLocal8Bit(buf);
        int areNo = sBuf.section("##", 0, 0).toInt();
        QString fileName = sBuf.section("##", 1, 1);
        QString filePath = QString("%0/%1/").arg(qApp->applicationDirPath()).arg(areNo);
        QDir().mkdir(filePath);
        filePath += fileName;

        m_file.setFileName(filePath);
        m_file.open(QIODevice::WriteOnly);

        m_fileSize = sBuf.section("##", 2, 2).toInt();

        write("Completed!");
    }
    else
    {
        qint64 len = m_file.write(buf);
        m_blockSize += len;

        if (m_blockSize == m_fileSize)
        {
            m_file.close();
            m_bStart = true;
            m_blockSize = 0;

            write("Completed!");
        }
    }
}

void DataSocket::slotExport()
{
    QString fileFullPath = QString("%0/%1/%2").arg(qApp->applicationDirPath()).arg(areaNo).arg(sFileName);
    QFile file;
    file.setFileName(fileFullPath);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QFileInfo fileInfo = fileFullPath;
    fileSize = qMin(fileSize, fileInfo.size() - startPos);
    QString sHeader = QString("%0##%1##%2").arg(areaNo).arg(fileInfo.fileName()).arg(fileSize);
    qint64 len = write(sHeader.toLocal8Bit());
    waitForReadyRead();
    if (len == -1)
        return;
    SCOPE_EXIT([&]{ file.close(); });

    file.seek(startPos);

    qint64 bufferLen = 0;
    do
    {
        char buffer[4 * 1024] = {0};
        qint64 len = file.read(buffer, sizeof(buffer));
        len = write(buffer, len);
        bufferLen += len;

    } while (bufferLen < fileSize);

    waitForReadyRead();
}

void DataSocket::initData()
{
    m_blockSize = 0;
    m_fileSize = 0;
    m_bStart = true;
}
