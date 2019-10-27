#ifndef HOSTMACHINESERVER_H
#define HOSTMACHINESERVER_H

#include <QTcpServer>

class HostMachineServer : public QTcpServer
{
    Q_OBJECT

public:
    HostMachineServer(QObject *parent = 0);
    ~HostMachineServer();

protected:
    virtual void incomingConnection(qintptr handle);
};

#endif // HOSTMACHINESERVER_H
