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

    // ��¼����
    bool IsRecordStop() const { return m_bRecordStop; }
    void SetRecordStop(bool val) { m_bRecordStop = val; }
    // �ط�����
    bool IsPlaybackStop() const { return m_bPlaybackStop; }
    void SetPlaybackStop(bool val) { m_bPlaybackStop = val; }
    // ��������
    bool IsExportStop() const { return m_bExportStop; }
    void SetExportStop(bool val) { m_bExportStop = val; }
    // ��������
    bool IsImportStop() const { return m_bImportStop; }
    void SetImportStop(bool val) { m_bImportStop = val; }

private:
    CSocketManager(void);
    ~CSocketManager(void);

    static CSocketManager* m_pInstance;

    CmdSocket* m_pCmdSocket;
    DataSocket* m_pDataSocket;

    bool m_bRecordStop, m_bPlaybackStop, m_bImportStop, m_bExportStop;
};

