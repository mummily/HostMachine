#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>

enum RequestType // 请求类型
{
    CS_CheckSelf = 0x11,
    CS_Format = 0xA1,
};

enum RespondType // 应答类型
{
    SC_CheckSelf = 0x1011,
    SC_Format = 0x10A1
};

class ClientSocket : public QTcpSocket
{
    Q_OBJECT

public:
    ClientSocket(QObject *parent);
    ~ClientSocket();

    void respondCheckSelf();
    void respondFormat(quint32 size0, quint32 size1);
private slots:
    void readClient();
};

#endif // CLIENTSOCKET_H
