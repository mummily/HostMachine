#include "cmdsocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"
#include "QThread"
#include <QDir>
#include "common.h"

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
    if (requestType == CS_CheckSelf) // �Լ�
    {
        respondCheckSelf();
    }
    else if (requestType == CS_Format) // ��ʽ��
    {
        quint32 size0, size1, size2, size3, size4;
        in >> size0 >> size1 >> size2 >> size3 >>size4;
        respondFormat(size0, size1, size2, size3, size4);
    }
    else if (requestType == CS_SystemConfig) // ϵͳ����
    {
        quint32 choice, setting;
        in >> choice >> setting;
        respondSystemConfig(choice, setting);
    }
    else if (requestType == CS_Record) // ��¼
    {
        quint32 areano;
        quint64 time;
        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);
        in >> areano >> time >> filename;
        respondRecord(areano, time, QString::fromLocal8Bit(filename));
        // delete[] filename;
    }
    else if (requestType == CS_PlayBack) // �ط�
    {
        quint32 data1, data2, data3, data4, data5, data6, data7;
        in >> data1 >> data2 >> data3 >> data4 >> data5 >> data6 >> data7;
        respondPlayBack(data1, data2, data3, data4, data5, data6, data7);
    }
    else if (requestType == CS_TaskStop) // ����ֹͣ
    {
        quint32 areano, tasktype;
        in >> areano >> tasktype;
        respondTaskStop(areano, tasktype);
    }
    else if (requestType == CS_Delete) // �����ļ�ɾ��
    {
        quint32 areano, fileno;
        in >> areano >> fileno;
        respondDelete(areano, fileno);
    }
    else if (requestType == CS_Refresh) // �����ļ�ˢ��
    {
        quint32 areano, fileno, filenum;
        in >> areano >> fileno >> filenum;
        respondRefresh(areano, fileno, filenum);
    }
    else if (requestType == CS_Import) // ����
    {
        quint32 areano;
        float filesize;
        quint64 time;
        in >> areano >> filesize >> time;

        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);
        in.readRawData(filename, 128);

        respondImport(areano, filesize, QDateTime::fromMSecsSinceEpoch(time), filename);
    }
}


void CmdSocket::respondImport(quint32 areano, float filesize, QDateTime time, char* filename)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Import) << areano;
    out.writeRawData(filename, 128);
    quint32 result = 0/*qrand() % 3*/; // 0x00 �ɹ� 0x01 ��Դ���� 0x02 ����
    out << result;
    write(block);
}

void CmdSocket::respondCheckSelf()
{
    QStringList filter;
    filter<<"*.*";

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_CheckSelf); // ������
    for (int nIndex = 0; nIndex < 5; ++nIndex)
    {
        QString sDir = QString("D:/HostMachine/%0").arg(nIndex);
        QDir dir(sDir);
        dir.setNameFilters(filter);
        QList<QFileInfo> fileInfo(dir.entryInfoList(filter, QDir::Files));

        out << quint32(nIndex) // ������
            << quint32(100) // ������С
            << quint32(qrand() % 100)  // ����δʹ�ô�С
            << quint32(fileInfo.count())  // �����ļ�����
            << quint32(qrand() % 3);  // ����״̬
    }

    out << quint32(qrand() % 2)   // ͨ��״̬
        << quint32(qrand() % 2)   // ͨ��ѡ��
        << quint32(qrand() % 5)   // ����
        << quint32(0)   // �̼��汾��
        << quint32(0);  // FPGA�汾��

    write(block);
}

void CmdSocket::respondFormat(quint32 size0, quint32 size1, quint32 size2, quint32 size3, quint32 size4)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Format) << quint32(qrand() % 2); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
}

void CmdSocket::respondSystemConfig(quint32 choice, quint32 setting)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_SystemConfig) << choice << quint32(qrand() % 2); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
}

void CmdSocket::respondRecord(quint32 areano, quint64 time, QString filename)
{
    QDateTime datetime = QDateTime::fromMSecsSinceEpoch(time);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Record) << areano << quint32(qrand() % 2); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
}

void CmdSocket::respondPlayBack(quint32 data1, quint32 data2, 
    quint32 data3, quint32 data4, quint32 data5, quint32 data6, quint32 data7)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_PlayBack) << data1 << quint32(qrand() % 2); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
}

void CmdSocket::respondTaskStop(quint32 areano, quint32 tasktype)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_TaskStop) << areano << tasktype << quint32(qrand() % 2); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
}

void CmdSocket::respondDelete(quint32 areano, float fileno)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Delete) << areano << quint32(qrand() % 2); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
}

void CmdSocket::respondRefresh(quint32 areano, quint32 fileno, quint32 filenum)
{
    QString sDir = QString("D:/HostMachine/%0").arg(areano);
    QDir dir(sDir);

    QList<QFileInfo> fileInfos(dir.entryInfoList(QDir::Files));
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Refresh) << areano << fileno << fileInfos.count(); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    int nIndex = 1;
    foreach(QFileInfo fileInfo, fileInfos)
    {
        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);

        QByteArray ba = fileInfo.fileName().toLatin1();
        filename = ba.data();

        out.writeRawData(filename, 128);
        out << fileInfo.created().toMSecsSinceEpoch() << quint32(nIndex++) << quint64(fileInfo.size());
    }
    write(block);
}
