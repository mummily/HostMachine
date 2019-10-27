#include "hostmachineserver.h"
#include "clientsocket.h"

HostMachineServer::HostMachineServer(QObject *parent/* = 0*/)
    : QTcpServer(parent)
{

}

HostMachineServer::~HostMachineServer()
{

}

void HostMachineServer::incomingConnection(qintptr handle)
{
    ClientSocket *socket = new ClientSocket(this);
    socket->setSocketDescriptor(handle);
}
