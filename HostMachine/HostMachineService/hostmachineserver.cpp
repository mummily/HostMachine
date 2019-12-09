#include "hostmachineserver.h"
#include "cmdsocket.h"
#include "datasocket.h"
#include "SocketManager.h"
#include "..\HostMachine\taskcommon.h"

HostMachineServer::HostMachineServer(QObject *parent/* = 0*/)
    : QTcpServer(parent)
{
}

HostMachineServer::~HostMachineServer()
{

}

void HostMachineServer::incomingConnection(qintptr handle)
{
    if (serverPort() == c_uCommandPort)
    {
        CmdSocket *cmdSocket = new CmdSocket(this);
        cmdSocket->setSocketDescriptor(handle);
        CSocketManager::getInstance()->SetCmdSocket(cmdSocket);
    }
    else if (serverPort() == c_uDataPort)
    {
        DataSocket *dataSocket = new DataSocket(this);
        dataSocket->setSocketDescriptor(handle);
        CSocketManager::getInstance()->SetDataSocket(dataSocket);
    }
}
