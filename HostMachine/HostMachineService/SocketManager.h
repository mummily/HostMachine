#pragma once

class CmdSocket;
class DataSocket;
class CSocketManager
{
public:
    static CSocketManager* getInstance();
    static void freeInstance() { delete m_pInstance; }

    CmdSocket* cmdSocket() const { return m_pCmdSocket; }
    void SetCmdSocket(CmdSocket* val) { m_pCmdSocket = val; }

    DataSocket* dataSocket() const { return m_pDataSocket; }
    void SetDataSocket(DataSocket* val) { m_pDataSocket = val; }

private:
    CSocketManager(void);
    ~CSocketManager(void);

    static CSocketManager* m_pInstance;

    CmdSocket* m_pCmdSocket;
    DataSocket* m_pDataSocket;
};

