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
    else if (requestType == CS_Import) // ����
    {
        quint32 areano;
        float filesize;
        quint64 time;
        char* filename = new char[128];
        memset(filename, 0, sizeof(char)*128);
        in >> areano >> filesize >> time >> filename;
        respondImport(areano, filesize, QDateTime::fromMSecsSinceEpoch(time), QString::fromLocal8Bit(filename));
    }
    else if (requestType == CS_Export) // ����
    {
        quint32 areano;
        float fileno, startpos, exportsize;
        in >> areano >> fileno >> startpos >> exportsize;
        respondExport(areano, fileno, startpos, exportsize);
    }
    else if (requestType == CS_Stop) // ����ֹͣ
    {
        quint32 areano;
        in >> areano;
        respondStop(areano);
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
}

void ClientSocket::respondCheckSelf()
{
    QThread::currentThread()->sleep(5);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_CheckSelf); // ������
    for (int nIndex = 0; nIndex < 5; ++nIndex)
    {
        out << quint32(nIndex) // ������
            << quint32(100) // ������С
            << quint32(qrand() % 100)  // ����δʹ�ô�С
            << quint32(qrand() % 10)  // �����ļ�����
            << quint32(qrand() % 3);  // ����״̬
    }

    out << quint32(qrand() % 1)   // ͨ��״̬
        << quint32(qrand() % 1)   // ͨ��ѡ��
        << quint32(qrand() % 5)   // ����
        << quint32(0)   // �̼��汾��
        << quint32(0);  // FPGA�汾��

    write(block);
    waitForReadyRead();
}

void ClientSocket::respondFormat(quint32 size0, quint32 size1, quint32 size2, quint32 size3, quint32 size4)
{
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Format) << quint32(qrand() % 1); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
    waitForReadyRead();
}

void ClientSocket::respondSystemConfig(quint32 choice, quint32 setting)
{
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_SystemConfig) << quint32(qrand() % 1); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
    waitForReadyRead();
}

void ClientSocket::respondRecord(quint32 areano, quint64 time, QString filename)
{
    QDateTime datetime = QDateTime::fromMSecsSinceEpoch(time);
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Record) << areano << quint32(qrand() % 1); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
    waitForReadyRead();
}

void ClientSocket::respondPlayBack(quint32 data1, quint32 data2, 
    quint32 data3, quint32 data4, quint32 data5, quint32 data6, quint32 data7)
{
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_PlayBack) << data1 << quint32(qrand() % 1); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
    waitForReadyRead();
}

void ClientSocket::respondImport(quint32 areano, float filesize, QDateTime time, QString filename)
{
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Import) << areano << quint32(qrand() % 1); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
    waitForReadyRead();
}

void ClientSocket::respondExport(quint32 areano, float fileno, float startpos, float exportsize)
{
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Export) << areano << quint32(qrand() % 1); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
    waitForReadyRead();
}

void ClientSocket::respondStop(quint32 areano)
{
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Stop) << areano << quint32(qrand() % 1); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
    waitForReadyRead();
}

void ClientSocket::respondDelete(quint32 areano, float fileno)
{
    QThread::currentThread()->sleep(3);
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Delete) << areano << quint32(qrand() % 1); // 0x00 �ɹ� 0x01 ʧ�� ���� ����
    write(block);
    waitForReadyRead();
}

void ClientSocket::respondRefresh(quint32 areano, quint32 fileno, quint32 filenum)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Refresh) << areano << fileno << filenum; // 0x00 �ɹ� 0x01 ʧ�� ���� ����
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
    waitForReadyRead();
}