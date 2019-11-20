#include "datasocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"
#include "QThread"
#include <QDir>
#include "common.h"
#include <QFile>

DataSocket::DataSocket(QObject *parent)
    : QTcpSocket(parent), m_blockSize(0), m_fileSize(0)
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

    qint32 requestType;
    in >> requestType;
    if (requestType == CS_Export) // 导出
    {
        qint32 areano;
        float fileno, startpos, exportsize;
        in >> areano >> fileno >> startpos >> exportsize;
        respondExport(areano, fileno, startpos, exportsize);
    }
    else if (requestType == CS_Import) // 导入
    {
        qint32 type;
        in >> type;
        if (type == 0)
        {
            in >> m_fileSize;

            m_file = new QFile(this);
            m_file->setFileName("Test.txt");
            m_file->open(QIODevice::WriteOnly);

            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_5);
            out << quint32(SC_Import);
            write(block);
        }
        else
        {
            qint32 len;
            in >> len;
            qDebug() << len << endl;
            char buffer[4*1024];
            in.readRawData(buffer, len);
            m_file->write(buffer, len);
            if (len < 4*1024)
            {
                m_file->close();
                m_fileSize = 0;
            }
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
