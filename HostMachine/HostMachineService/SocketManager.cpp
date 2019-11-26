#include "SocketManager.h"

CSocketManager* CSocketManager::m_pInstance = nullptr;
CSocketManager::CSocketManager(void)
{
    m_pCmdSocket = nullptr;
    m_pDataSocket = nullptr;
    
    m_bRecordStop = false;
    m_bPlaybackStop = false;
    m_bImportStop = false;
    m_bExportStop = false;
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