#pragma once
#include "common.h"
#include "qglobal.h"
class CTaskStoper
{
public:
    static CTaskStoper* getInstance();
    static void freeInstance() { delete m_pInstance; }

    RequestType getRequestType() const { return requestType; }
    void setRequestType(RequestType val) { requestType = val; }

    RespondType getRespondType() const { return respondType; }
    void setRespondType(RespondType val) { respondType = val; }

    qint32 getAreano() const { return areano; }
    void setAreano(qint32 val) { areano = val; }
    
    qint32 getResult() const { return result; }
    void setResult(qint32 val) { result = val; }

private:
    CTaskStoper(void);
    ~CTaskStoper(void);

    static CTaskStoper* m_pInstance;
    RequestType requestType;
    RespondType respondType;

    qint32 areano, result;
};

