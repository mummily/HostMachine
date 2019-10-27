#include "clientsocket.h"
#include "QDataStream"
#include "QDateTime"
#include "QMessageBox"

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
    if (requestType == 0x11) // �Լ�
    {
        respondCheckSelf();
    }
    else if (requestType == CS_Format) // ��ʽ��
    {
        quint32 size0, size1;
        in >> size0 >> size1;
        respondFormat(size0, size1);
    }
    else if (requestType == 0xB1) // ϵͳ����
    {
        quint32 choice, setting;
        in >> choice >> setting;
    }
    else if (requestType == 0x21) // ��¼
    {
        quint32 no;
        QDate date;
        QTime time;
        QString filename;
        in >> no >> date >> time >> filename;
    }
    else if (requestType == 0x31) // �ط�
    {
        quint32 data1, data2, data3, data4, data5, data6, data7;
        in >> data1 >> data2 >> data3 >> data4 >> data5 >> data6 >> data7;
    }
}

void ClientSocket::respondCheckSelf()
{

}

void ClientSocket::respondFormat(quint32 size0, quint32 size1)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint32(SC_Format) << quint32(0x00); // 0x00 ��ʽ���ɹ� 0x01 ʧ�� ���� ����
    write(block);
}
