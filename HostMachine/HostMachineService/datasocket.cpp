#include "datasocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"
#include <QApplication>
#include "QThread"
#include <QDir>
#include "common.h"
#include <QFile>

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

void DataSocket::respondExport(quint32 areano, float fileno, float startpos, float exportsize)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Export) << areano << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}
