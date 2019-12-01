#include "SocketManager.h"

CSocketManager* CSocketManager::m_pInstance = nullptr;
CSocketManager::CSocketManager(void)
{
    m_pCmdSocket = nullptr;
    m_pDataSocket = nullptr;
}


CSocketManager::~CSocketManager(void)
{
}

CSocketManager* CSocketManager::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CSocketManager;
    }
    return m_pInstance;
}