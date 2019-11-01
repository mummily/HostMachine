#include "clientsocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"
#include "QThread"

ClientSocket::ClientSocket(QObject *parent)
    : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnect()), this, SLOT(deleteLater()));
}

ClientSocket::~ClientSocket()
{

}

void ClientSocket::readClient()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_5);

    if (bytesAvailable() < sizeof(quint32))
        return;

    quint32 requestType;
    in >> requestType;
    if (requestType == CS_CheckSelf) // 自检
    {
        respondCheckSelf();
    }
    else if (requestType == CS_Format) // 格式化
    {
        quint32 size0, size1, size2, size3, size4;
        in >> size0 >> size1 >> size2 >> size3 >>size4;
        respondFormat(size0, size1, size2, size3, size4);
    }
    else if (requestType == 0xB1) // 系统配置
    {
        quint32 choice, setting;
        in >> choice >> setting;
    }
    else if (requestType == 0x21) // 记录
    {
        quint32 no;
        QDate date;
        QTime time;
        QString filename;
        in >> no >> date >> time >> filename;
    }
    else if (requestType == 0x31) // 回放
    {
        quint32 data1, data2, data3, data4, data5, data6, data7;
        in >> data1 >> data2 >> data3 >> data4 >> data5 >> data6 >> data7;
    }
}

void ClientSocket::respondCheckSelf()
{
    QThread::currentThread()->sleep(5);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_CheckSelf); // 类型码
    for (int nIndex = 0; nIndex < 5; ++nIndex)
    {
        out << quint32(nIndex) // 分区号
            << quint32(100) // 分区大小
            << quint32(30)  // 分区未使用大小
            << quint32(10)  // 分区文件个数
            << quint32(0)   // 分区状态
            << quint32(0)   // 通道状态
            << quint32(0)   // 通道选择
            << quint32(1)   // 带宽
            << quint32(0)   // 固件版本号
            << quint32(0);  // FPGA版本号
    }
    write(block);
}

void ClientSocket::respondFormat(quint32 size0, quint32 size1, quint32 size2, quint32 size3, quint32 size4)
{
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Format) << quint32(0x00); // 0x00 格式化成功 0x01 失败 其它 保留
    write(block);
}
