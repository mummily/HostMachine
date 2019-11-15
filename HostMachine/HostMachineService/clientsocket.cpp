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
    else if (requestType == CS_SystemConfig) // 系统配置
    {
        quint32 choice, setting;
        in >> choice >> setting;
        respondSystemConfig(choice, setting);
    }
    else if (requestType == CS_Record) // 记录
    {
        quint32 areano;
        quint64 time;
        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);
        in >> areano >> time >> filename;
        respondRecord(areano, time, QString::fromLocal8Bit(filename));
        // delete[] filename;
    }
    else if (requestType == CS_PlayBack) // 回放
    {
        quint32 data1, data2, data3, data4, data5, data6, data7;
        in >> data1 >> data2 >> data3 >> data4 >> data5 >> data6 >> data7;
        respondPlayBack(data1, data2, data3, data4, data5, data6, data7);
    }
    else if (requestType == CS_Import) // 导入
    {
        quint32 areano;
        float filesize;
        quint64 time;
        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);
        in >> areano >> filesize >> time >> filename;
        respondImport(areano, filesize, QDateTime::fromMSecsSinceEpoch(time), QString::fromLocal8Bit(filename));
    }
    else if (requestType == CS_Export) // 导出
    {
        quint32 areano;
        float fileno, startpos, exportsize;
        in >> areano >> fileno >> startpos >> exportsize;
        respondExport(areano, fileno, startpos, exportsize);
    }
    else if (requestType == CS_TaskStop) // 任务停止
    {
        quint32 areano, tasktype;
        in >> areano >> tasktype;
        respondTaskStop(areano, tasktype);
    }
    else if (requestType == CS_Delete) // 分区文件删除
    {
        quint32 areano, fileno;
        in >> areano >> fileno;
        respondDelete(areano, fileno);
    }
    else if (requestType == CS_Refresh) // 分区文件刷新
    {
        quint32 areano, fileno, filenum;
        in >> areano >> fileno >> filenum;
        respondRefresh(areano, fileno, filenum);
    }
}

void ClientSocket::respondCheckSelf()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_CheckSelf); // 类型码
    for (int nIndex = 0; nIndex < 5; ++nIndex)
    {
        out << quint32(nIndex) // 分区号
            << quint32(100) // 分区大小
            << quint32(qrand() % 100)  // 分区未使用大小
            << quint32(qrand() % 10)  // 分区文件个数
            << quint32(qrand() % 3);  // 分区状态
    }

    out << quint32(qrand() % 2)   // 通道状态
        << quint32(qrand() % 2)   // 通道选择
        << quint32(qrand() % 5)   // 带宽
        << quint32(0)   // 固件版本号
        << quint32(0);  // FPGA版本号

    write(block);
}

void ClientSocket::respondFormat(quint32 size0, quint32 size1, quint32 size2, quint32 size3, quint32 size4)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Format) << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void ClientSocket::respondSystemConfig(quint32 choice, quint32 setting)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_SystemConfig) << choice << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void ClientSocket::respondRecord(quint32 areano, quint64 time, QString filename)
{
    QDateTime datetime = QDateTime::fromMSecsSinceEpoch(time);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Record) << areano << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void ClientSocket::respondPlayBack(quint32 data1, quint32 data2, 
    quint32 data3, quint32 data4, quint32 data5, quint32 data6, quint32 data7)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_PlayBack) << data1 << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void ClientSocket::respondImport(quint32 areano, float filesize, QDateTime time, QString filename)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Import) << areano << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void ClientSocket::respondExport(quint32 areano, float fileno, float startpos, float exportsize)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Export) << areano << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void ClientSocket::respondTaskStop(quint32 areano, quint32 tasktype)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_TaskStop) << areano << tasktype << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void ClientSocket::respondDelete(quint32 areano, float fileno)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Delete) << areano << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void ClientSocket::respondRefresh(quint32 areano, quint32 fileno, quint32 filenum)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Refresh) << areano << fileno << filenum; // 0x00 成功 0x01 失败 其它 保留
    for (int nIndex=0; nIndex<filenum;++nIndex)
    {
        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);

        QString sFileName = QString("File%1").arg(nIndex+1);
        QByteArray ba = sFileName.toLatin1();
        filename = ba.data();

        out.writeRawData(filename, 128);
        out << QDateTime::currentDateTime().currentMSecsSinceEpoch() << quint32(nIndex+1) << float(nIndex+0.123);
    }
    write(block);
}
