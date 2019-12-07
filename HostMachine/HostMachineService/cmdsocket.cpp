#include "cmdsocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"
#include <QApplication>
#include "QThread"
#include <QDir>
#include "common.h"
#include "QTimer"
#include "datasocket.h"
#include "SocketManager.h"
#include "TaskStoper.h"

CmdSocket::CmdSocket(QObject *parent)
    : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnect()), this, SLOT(deleteLater()));
}

CmdSocket::~CmdSocket()
{

}

void CmdSocket::readClient()
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
        char filename[40] = {0};
        in >> areano >> time;
        in.readRawData(filename, sizeof(filename));
        respondRecord(areano, time, QString::fromLocal8Bit(filename));
    }
    else if (requestType == CS_PlayBack) // 回放
    {
        quint32 data1, data2, data3, data4, data5, data6, data7;
        in >> data1 >> data2 >> data3 >> data4 >> data5 >> data6 >> data7;
        respondPlayBack(data1, data2, data3, data4, data5, data6, data7);
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
    else if (requestType == CS_Import) // 导入
    {
        quint32 areano;
        float filesize;
        quint64 time;
        in >> areano >> filesize >> time;

        char filename[40] = {0};
        in.readRawData(filename, sizeof(filename));

        respondImport(areano, filesize, QDateTime::fromMSecsSinceEpoch(time), filename);
    }
    else if (requestType == CS_Export) // 导出
    {
        quint32 areano;
        in >> areano;

        char filename[40] = {0};
        in.readRawData(filename, sizeof(filename));

        float startpos, filesize;
        in >> startpos >> filesize;

        respondExport(areano, filename, startpos, filesize);
    }
    else if (requestType == CS_TaskQuery) // 任务查询
    {
        respondTaskQuery();
    }
}


void CmdSocket::respondImport(quint32 areano, float filesize, QDateTime time, char* filename)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Import) << areano;
    out.writeRawData(filename, 40);
    quint32 result = 0/*qrand() % 3*/; // 0x00 成功 0x01 资源不足 0x02 其它
    out << result;
    write(block);

    if (result == 0x00)
    {
        CSocketManager::getInstance()->dataSocket()->initData();
    }
}

void CmdSocket::respondCheckSelf()
{
    QStringList filter;
    filter<<"*.*";

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_CheckSelf) << quint32(5*100); // 类型码
    for (int nIndex = 0; nIndex < 5; ++nIndex)
    {
        QString sDir = QString("%0/%1").arg(qApp->applicationDirPath()).arg(nIndex);
        QDir dir(sDir);
        dir.setNameFilters(filter);
        QList<QFileInfo> fileInfo(dir.entryInfoList(filter, QDir::Files));

        out << quint32(100) // 分区大小
            << quint32(qrand() % 100)  // 分区未使用大小
            << quint32(fileInfo.count())  // 分区文件个数
            << quint32(qrand() % 3);  // 分区状态
    }

    out << quint32(qrand() % 2)   // 通道状态
        << quint32(qrand() % 2)   // 通道选择
        << quint32(qrand() % 5)   // 带宽
        << quint32(0)   // 固件版本号
        << quint32(0);  // FPGA版本号

    write(block);
}

void CmdSocket::respondFormat(quint32 size0, quint32 size1, quint32 size2, quint32 size3, quint32 size4)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Format) << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void CmdSocket::respondSystemConfig(quint32 choice, quint32 setting)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_SystemConfig) << choice << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void CmdSocket::respondRecord(quint32 areano, quint64 time, QString filename)
{
    QDateTime datetime = QDateTime::fromMSecsSinceEpoch(time);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Record) << areano << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void CmdSocket::respondPlayBack(quint32 data1, quint32 data2, 
    quint32 data3, quint32 data4, quint32 data5, quint32 data6, quint32 data7)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_PlayBack) << data1 << quint32(qrand() % 2); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void CmdSocket::respondTaskStop(quint32 areano, quint32 tasktype)
{
    CTaskStoper::getInstance()->setRequestType((RequestType)tasktype);

    QTimer::singleShot(10000, [&]()
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_5);

        qint32 result = 0x00;
        out << quint32(SC_TaskStop)
            << CTaskStoper::getInstance()->getAreano()
            << CTaskStoper::getInstance()->getRespondType()
            << CTaskStoper::getInstance()->getResult(); // 0x00 成功 0x01 失败 其它 保留
        write(block);
    });
}

void CmdSocket::respondDelete(quint32 areano, quint32 fileno)
{
    // QString sFileName = QString::fromLocal8Bit(filename);
    // QString sFileFullPath = QString("%0/%1/%2").arg(qApp->applicationDirPath()).arg(areano).arg(sFileName);
    bool bOk = true/*QFile::remove(sFileFullPath)*/;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Delete) << areano << (bOk ? quint32(0x00) : quint32(0x01)); // 0x00 成功 0x01 失败 其它 保留
    write(block);
}

void CmdSocket::respondRefresh(quint32 areano, quint32 fileno, quint32 filenum)
{
    QString filePath = QString("%0/%1/").arg(qApp->applicationDirPath()).arg(areano);
    QDir dir(filePath);

    QList<QFileInfo> fileInfos(dir.entryInfoList(QDir::Files));
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Refresh) << areano << fileInfos.count(); // 0x00 成功 0x01 失败 其它 保留
    int nIndex = 1;
    foreach(QFileInfo fileInfo, fileInfos)
    {
        char filename[40] = {0};
        QString sFileName = fileInfo.fileName();
        QByteArray ba = fileInfo.fileName().toLocal8Bit();
        strncpy(filename, ba.data(), sizeof(filename));

        out.writeRawData(filename, sizeof(filename));
        out << fileInfo.created().toMSecsSinceEpoch() << quint32(nIndex++) << quint32(fileInfo.size());
    }
    write(block);
}

void CmdSocket::respondExport(quint32 areano, char* filename, float startpos, float filesize)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    qint32 result = 0x00;
    out << quint32(SC_Export) << areano << result; // 0x00 开始导出 0x01 资源不足 其它 保留
    write(block);

    // 成功，开始导出
    if (result == 0x00)
    {
        CSocketManager::getInstance()->dataSocket()->areaNo = areano;
        CSocketManager::getInstance()->dataSocket()->sFileName = QString::fromLocal8Bit(filename);
        CSocketManager::getInstance()->dataSocket()->startPos = startpos * 1024;
        CSocketManager::getInstance()->dataSocket()->fileSize = filesize * 1024;

        QTimer::singleShot(10, CSocketManager::getInstance()->dataSocket(), SLOT(slotExport()));
    }
}

void CmdSocket::respondTaskQuery()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    qint32 result = 0x00;
    out << quint32(SC_TaskQuery);   // 0x00 开始导出 0x01 资源不足 其它 保留
    qint32 taskNum = 0/*qint32(qrand() % 5)*/;   // 4以内任务个数
    out << taskNum;
    for (qint32 taskIndex=0; taskIndex<taskNum; ++taskIndex)
    {
        out << qint32(qrand() % 2)  // 1 有效任务 0 无效任务
            << qint32(0)    // 分区
            << SC_Record    // 任务类型
            << qint32(100)  // 任务已完成大小 LBA
            << qint32(10)   // 任务速度 KB/s
            << qint32(22)   // 任务进度百分比
            << qint32(qrand() % 3); // 0 等待执行 1 执行中 2 已完成
    }

    write(block);
}
