#include "datasocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"
#include <QApplication>
#include "QThread"
#include <QDir>
#include "common.h"
#include <QFile>

const QString c_sImportHead= "{2585E781-1C60-416E-9A18-CC7ACD2522AF}";
const QString c_sExportHead= "{FFEE539A-6E91-4461-AD05-8B5F21CAF18D}";

DataSocket::DataSocket(QObject *parent)
    : QTcpSocket(parent), m_blockSize(0), m_fileSize(0), m_bStart(true)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnect()), this, SLOT(deleteLater()));
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
    if (m_bStart)
    {
        m_bStart = false;

        int areNo = QString(buf).section("##", 0, 0).toInt();
        QString fileName = QString(buf).section("##", 1, 1);
        QString filePath = QString("%0/%1/").arg(qApp->applicationDirPath()).arg(areNo);
        QDir().mkdir(filePath);
        filePath += fileName;

        m_file.setFileName(filePath);
        m_file.open(QIODevice::WriteOnly);

        m_fileSize = QString(buf).section("##", 2, 2).toInt();
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

void DataSocket::respondExport(QByteArray buf)
{
}
