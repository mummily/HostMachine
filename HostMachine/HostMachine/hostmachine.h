#ifndef HOSTMACHINE_H
#define HOSTMACHINE_H

#include <QtWidgets/QMainWindow>

using namespace std;
#include "common.h"
#include "tasktype.h"
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

// ������ʾ�����̿������
struct tagAreaProperties
{
    shared_ptr<tagAreaProperty> ldProperty1;    // ԭʼ���ݷ���
    shared_ptr<tagAreaProperty> ldProperty2;    // �״�������
    shared_ptr<tagAreaProperty> gdProperty1;    // ���ͼƬ����
    shared_ptr<tagAreaProperty> gdProperty2;    // �����Ƶ����
    shared_ptr<tagAreaProperty> hhProperty;     // ������ݷ���
    shared_ptr<tagChannelProperty> channelProperty; // ������Ϣ

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
    quint32 area;
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
            >> bandwidth
            >> hardversion
            >> fpgaversion;
    }
};

// �Լ�Ӧ��-�Լ���Ϣ
struct tagCheckSelf
{
    shared_ptr<tagAreaInfo> areaInfo0, areaInfo1, areaInfo2, areaInfo3, areaInfo4;
    shared_ptr<tagChannelInfo> channelInfo;
    quint32 totalsize;

    tagCheckSelf()
    {
    }
};

struct tagExportParam
{
    qint32 rowNo;
    float startPos, fileSize;
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
        // ����
        void slotExport();
        void slotForeachExport();
        // ֹͣ
        void slotStop();
        // ɾ��
        void slotDelete();
        // ˢ��
        void slotRefresh();

        // Init
        void slotInit();
        // Tab Changed
        void slotTabChanged(int index);
        void slotImportStart(qint32 areano, QString fileName, float buffer, float total);
        void slotImportUpdate(qint32 areano, QString fileName, float buffer, float total);
        void slotImportCompleted(qint32 areano, QString fileName, float buffer, float total);
        void slotExportStart(qint32 areano, QString fileName, float buffer, float total);
        void slotExportUpdate(qint32 areano, QString fileName, float buffer, float total);
        void slotExportCompleted(qint32 areano, QString fileName, float buffer, float total);

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
    void readCheckSelf();
    void readFormat(quint32 state);
    void readSystemConfig(quint32 choice, quint32 state);
    void readTaskQuery();
    void readRecord(quint32 area, quint32 state);

private:
    shared_ptr<tagAreaProperties>       m_spAreaProperties;
    shared_ptr<tagCheckSelf>            m_spcheckSelf;
    shared_ptr<TaskType>                m_spTaskType;
    shared_ptr<tagAreaFileInfos>        m_spFileInfos;
    QString                             m_sAddr;
    QList<shared_ptr<tagExportParam>>   m_lstExportParam;
    QList<shared_ptr<tagTaskInfo>>      m_lstTaskInfo;

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
    QElapsedTimer                       *m_pElapsedTimer;
    quint64                             m_nInterval;

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
