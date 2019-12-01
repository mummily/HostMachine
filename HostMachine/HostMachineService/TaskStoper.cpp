#include "TaskStoper.h"


CTaskStoper* CTaskStoper::m_pInstance = nullptr;
CTaskStoper::CTaskStoper(void)
{
    requestType = CS_Unknown;
    respondType = SC_Unknown;
    areano = 0;
    result = 0;
}


CTaskStoper::~CTaskStoper(void)
{
}

CTaskStoper* CTaskStoper::getInstance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new CTaskStoper;
    }
    return m_pInstance;
}
