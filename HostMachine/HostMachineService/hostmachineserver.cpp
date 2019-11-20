#include "hostmachineserver.h"
#include "cmdsocket.h"
#include "datasocket.h"

HostMachineServer::HostMachineServer(QObject *parent/* = 0*/)
    : QTcpServer(parent)
{
}

HostMachineServer::~HostMachineServer()
{

}

void HostMachineServer::incomingConnection(qintptr handle)
{
    if (serverPort() == 6178)
    {
        CmdSocket *socket = new CmdSocket(this);
        socket->setSocketDescriptor(handle);
    }
    else if (serverPort() == 6188)
    {
        DataSocket *socket = new DataSocket(this);
        socket->setSocketDescriptor(handle);
    }
}
