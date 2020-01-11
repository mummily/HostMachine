#ifndef HOSTMACHINE_H
#define HOSTMACHINE_H

#include <QtWidgets/QMainWindow>

using namespace std;
#include "common.h"
#include "taskcommon.h"
#include "QNetworkReply"

class QtProperty;
class QElapsedTimer;
class QtGroupPropertyManager;
class QtStringPropertyManager;
class QtDoublePropertyManager;
class QtIntPropertyManager;
class QtEnumPropertyManager;
class DecoratedDoublePropertyManager;

class QTableWidget;
class QTabWidget;
class QSplitter;
class QtTreePropertyBrowser;
class QLabel;
class QTcpSocket;
class CMWFileList;
class QFile;
class CDataSocket;
class TaskStopType;

// ��������
struct tagAreaProperty
{
    QtProperty *pItem1, *pItem2, *pItem3, *pItem4, *pItem5;
    tagAreaProperty()
    {
    }
};

// ͨ������
struct tagChannelProperty
{
    QtProperty *pItem1, *pItem2, *pItem3;
    tagChannelProperty()
    {
    }
};

// �汾������
struct tagVersionProperty
{
    QtProperty *pItem1, *pItem2;
    tagVersionProperty()
    {
    }
};

// ������ʾ�����̿������
struct tagAreaProperties
{
    shared_ptr<tagAreaProperty> ldProperty1;    // ԭʼ���ݷ���
    shared_ptr<tagAreaProperty> ldProperty2;    // �״�������
    shared_ptr<tagAreaProperty> gdProperty1;    // ���ͼƬ����
    shared_ptr<tagAreaProperty> gdProperty2;    // �����Ƶ����
    shared_ptr<tagAreaProperty> hhProperty;     // ������ݷ���
    shared_ptr<tagChannelProperty> channelProperty; // ������Ϣ
    shared_ptr<tagVersionProperty> versionProperty; // �汾����Ϣ

    tagAreaProperties()
    {
    }
};

// �����ѯӦ��-������Ϣ
struct tagTaskInfo
{
    quint32 flag; // ��� 1-��Ч���� 0-��Ч����
    quint32 area; // ���� 0-0���� 1-1����
    quint32 type; // �������� 0-����0 1-����1 2-���뵼�� 3-�ط�
    quint32 finishedsize; // ��������ɴ�С
    quint32 speed; // �����ٶ�
    quint32 percent; // ������Ȱٷֱ�
    quint32 state; // ����״̬ 0-�ȴ�ִ�� 1-ִ���� 2-�����

    tagTaskInfo()
    {
    }
};

// ������Ϣ
struct tagAreaInfo
{
    quint32 areasize;
    quint32 areaunuse;
    quint32 areafilenum;
    quint32 areastate;

    tagAreaInfo()
    {
    }

    void read(QDataStream& in)
    {
        in >> areasize
            >> areaunuse
            >> areafilenum
            >> areastate;
    }
};

// ͨ����Ϣ
struct tagChannelInfo
{
    quint32 state;
    quint32 choice;
    quint32 bandwidth;
    quint32 hardversion;
    quint32 fpgaversion;

    tagChannelInfo()
    {
    }

    void read(QDataStream& in)
    {
        in>> state
            >> choice
            >> bandwidth;
    }
};

// �汾����Ϣ
struct tagVersionInfo
{
    quint32 hardversion;
    quint32 fpgaversion;

    tagVersionInfo()
    {
    }

    void read(QDataStream& in)
    {
        in>> hardversion
            >> fpgaversion;
    }
};

// �Լ�Ӧ��-�Լ���Ϣ
struct tagCheckSelf
{
    shared_ptr<tagAreaInfo> areaInfo0, areaInfo1, areaInfo2, areaInfo3, areaInfo4;
    shared_ptr<tagChannelInfo> channelInfo;
    shared_ptr<tagVersionInfo> versionInfo;
    quint32 totalsize;

    tagCheckSelf()
    {
    }
};

struct tagImportParam
{
    qint32 areano;
    QString filePath;
    tagImportParam(qint32 _areano, QString _filePath)
        : areano(_areano), filePath(_filePath)
    {
    }
};

struct tagTaskQueryParam
{
    qint32 type; // 0-��¼ 1-���뵼��
    qint32 areano; // ����
    qint64 filesize; // �ļ��ܴ�С
    QDateTime dtStart; // ����ʼʱ��
    tagTaskQueryParam(qint32 _type, qint32 _areano, qint64 _filesize, QDateTime _dtStart)
        : type(_type), areano(_areano), filesize(_filesize), dtStart(_dtStart)
    {
    }
};

struct tagExportParam
{
    qint32 fileNo;
    qint32 startPos, fileSize;
    QString filePath;
    tagExportParam()
    {
    }
};

class HostMachine : public QMainWindow
{
    Q_OBJECT

public:
    HostMachine(QWidget *parent = 0);
    ~HostMachine();

    private slots:
        // TCP
        void connectedCmd();
        void disconnectCmd();
        void readyReadCmd();
        void errorCmd();

        void connectedData();
        void disconnectData();
        void errorData();

        // Menu
        // IP����
        void slotIPSetting();
        // �Լ�
        void slotCheckSelf();
        // ��ʽ��
        void slotFormat();
        // ϵͳ����
        void slotSystemConfig();
        // �����ѯ
        void slotTaskQuery();
        // ��־��¼
        void slotLogRecord(QString sText);
        void slotLogRecordAct();
        // ��¼
        void slotRecord();
        // �ط�
        void slotPlayBack();
        // ����
        void slotImport();
        void slotForeachImport();
        // ����
        void slotExport();
        void slotForeachExport();
        // ֹͣ
        void slotStop();
        // ����ֹͣ
        void slotTaskStop();
        // ɾ��
        void slotDelete();
        // ˢ��
        void slotRefresh();
        // ���������ѯ
        void slotTaskQueryStart();

        // Init
        void slotInit();
        // Tab Changed
        void slotTabChanged(int index);
        void slotImportStart(qint32 areano, QString fileName, qint64 buffer, qint64 total);
        void slotImportUpdate(qint32 areano, QString fileName, qint64 buffer, qint64 total);
        void slotImportCompleted(qint32 areano, QString fileName, qint64 buffer, qint64 total);
        void slotExportStart(qint32 areano, QString fileName, qint64 buffer, qint64 total);
        void slotExportUpdate(qint32 areano, QString fileName, qint64 buffer, qint64 total);
        void slotExportCompleted(qint32 areano, QString fileName, qint64 buffer, qint64 total);

private:
    void initUI();
    void initLayout();
    void initConnect();
    void initData();
    void closeLog();

    void initTaskWgt();
    void initPropertyWgt();

    void reallyCheckSelf();
    void reallyRefresh();
    void reallyTaskQuery();
    void reallyTaskStop(qint32 tasktype);

    void readCheckSelf();
    void readFormat(quint32 state);
    void readSystemConfig(quint32 choice, quint32 state);
    void readTaskQuery();

    bool reConnectCmd();
    bool reConnectData();
    bool queryTaskInvalid();

private:
    shared_ptr<tagAreaProperties>       m_spAreaProperties;
    shared_ptr<tagCheckSelf>            m_spcheckSelf;
    shared_ptr<TaskStopType>            m_spTaskStopType;
    QString                             m_sAddr;
    QList<shared_ptr<tagExportParam>>   m_lstExportParam;
    QList<shared_ptr<tagImportParam>>   m_lstImportParam;
    QList<shared_ptr<tagTaskInfo>>      m_lstTaskInfo;
    QList<shared_ptr<tagTaskQueryParam>>m_lstTaskQueryParam;

private:
    QAction                             *m_pActCheckSelf;       // �Լ�
    QAction                             *m_pActFormat;          // ��ʽ��
    QAction                             *m_pActIPSetting;       // IP����
    QAction                             *m_pActSystemConfig;    //ϵͳ����
    QAction                             *m_pActAbout;           // ����
    QMenu                               *m_pMenuSystemControl;

    QTcpSocket                          *m_pCmdSocket;          // ����Socket
    CDataSocket                         *m_pDataSocket;         // ����Socket

    CMWFileList                         *m_pLDOriginalWgt;      // �״�ԭʼ���ݷ���
    CMWFileList                         *m_pLDResultWgt;        // �״������ݷ���
    CMWFileList                         *m_pGDImgWgt;           // ���ͼƬ����
    CMWFileList                         *m_pGDVidioWgt;         // �����Ƶ����
    CMWFileList                         *m_pHHDataWgt;          // ������ݷ���

    QTableWidget                        *m_pTaskWgt;            // �����б��
    QElapsedTimer                       *m_pElapsedTimer;       // ���뵼�����¼��
    QTimer                              *m_pTimer;              // �����ѯ��ʱ��
    int                                 m_nTimer;               // �����ѯ������Ĵ���
    quint64                             m_nProgressBarUpdateInterval;
    bool                                m_bShowTaskStop;        // �Ƿ���ʾ����ֹͣ��

    QtTreePropertyBrowser               *m_pPropertyWgt;        // ���̿������

    QTabWidget                          *m_pTabWgt;
    QSplitter                           *m_pSplitter;
    QLabel                              *m_pIPLabel;            // ״̬
    QLabel                              *m_pCmdLabel;           // ״̬
    QLabel                              *m_pDataLabel;          // ״̬
    QFile                               *m_pLog;

    QtGroupPropertyManager              *m_groupManager;
    QtStringPropertyManager             *m_stringManager;
    DecoratedDoublePropertyManager      *m_doubleManager;
    QtIntPropertyManager                *m_intManager;
    QtEnumPropertyManager               *m_enumManager;
};

#endif // HOSTMACHINE_H
