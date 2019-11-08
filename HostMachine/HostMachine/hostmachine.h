#ifndef HOSTMACHINE_H
#define HOSTMACHINE_H

#include <QtWidgets/QMainWindow>
#include <list>
#include <QDataStream>
#include <QDateTime>
using namespace std;

class QtProperty;

class QtGroupPropertyManager;
class QtStringPropertyManager;
class QtDoublePropertyManager;
class QtIntPropertyManager;
class QtEnumPropertyManager;
class DecoratedDoublePropertyManager;

// ��������
enum RequestType
{
    CS_CheckSelf = 0x11,    // �Լ�
    CS_Format = 0xA1,       // ��ʽ��
    CS_SystemConfig = 0xB1, // ϵͳ����
    CS_Record = 0x21,       // ��¼
    CS_PlayBack = 0x31,     // �ط�
    CS_Import = 0x41,       // ����
    CS_Export = 0x51,       // ����
    CS_Stop = 0x61,         // ֹͣ
    CS_Delete = 0x71,       // ɾ��
    CS_Refresh = 0x81,      // ˢ��
    CS_TaskQuery = 0x91,    // �����ѯ
    CS_TaskStop = 0xC1,     // ����ֹͣ
};

// Ӧ������
enum RespondType
{
    SC_CheckSelf = 0x1011,      // �Լ�
    SC_Format = 0x10A1,         // ��ʽ��
    SC_SystemConfig = 0x10B1,   // ϵͳ����
    SC_Record = 0x1021,         // ��¼
    SC_PlayBack = 0x1031,       // �ط�
    SC_Import = 0x1041,         // ����
    SC_Export = 0x1051,         // ����
    SC_Stop = 0x1061,           // ֹͣ
    SC_Delete = 0x1071,         // ɾ��
    SC_Refresh = 0x1081,        // ˢ��
    SC_TaskQuery = 0x1091,      // �����ѯ
    SC_TaskStop = 0x10C1,       // ����ֹͣ
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
        in >> area
            >> areasize
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

    tagCheckSelf()
    {

    }
};

// ��������
struct tagAreaProperty
{
    QtProperty* pItem1;
    QtProperty* pItem2;
    QtProperty* pItem3;
    QtProperty* pItem4;
    QtProperty* pItem5;

    tagAreaProperty()
    {

    }
};

struct tagChannelProperty
{
    QtProperty* pItem1;
    QtProperty* pItem2;
    QtProperty* pItem3;
    
    tagChannelProperty()
    {

    }
};

struct tagAreaProperties
{
    shared_ptr<tagAreaProperty> ldProperty1;
    shared_ptr<tagAreaProperty> ldProperty2;
    shared_ptr<tagAreaProperty> gdProperty1;
    shared_ptr<tagAreaProperty> gdProperty2;
    shared_ptr<tagAreaProperty> hhProperty;
    shared_ptr<tagChannelProperty> channelProperty;
    
    tagAreaProperties()
    {

    }
};

struct tagAreaFileInfo
{
    QString sFileName;
    QDateTime datetime;
    quint32 fileno;
    float filesize;

    tagAreaFileInfo()
    {

    }
};

struct tagAreaFileInfos
{
    quint32 areano;
    quint32 fileno;
    quint32 filenum;
    list<shared_ptr<tagAreaFileInfo>> lstFileInfo;
    tagAreaFileInfos()
    {

    }
};

class QTableWidget;
class QTabWidget;
class QSplitter;
class QtTreePropertyBrowser;
class QFrame;
class QLabel;
class QTcpSocket;
class HostMachine : public QMainWindow
{
    Q_OBJECT

public:
    HostMachine(QWidget *parent = 0);
    ~HostMachine();

private:
    void initUI();
    void initTcp();
    void initLayout();
    void initConnect();

    void initLDDataWgt();
    void initGDDataWgt();
    void initHHDataWgt();
    void initTaskWgt();
    void initLogWgt();
    void initPropertyWgt1();
    void initPropertyWgt2();

    private slots:
        // TCP
        void connected();
        void disconnect();
        void readyRead();
        void error();

        // Menu
        // IP����
        void slotIPSetting();
        // �Լ�
        void slotCheckSelf();
        // ��ʽ��
        void slotFormat();
        // ϵͳ����
        void slotSystemConfig();
        // ��¼
        void slotRecord();
        // �ط�
        void slotPlayBack();
        // ����
        void slotImport();
        // ����
        void slotExport();
        // ֹͣ
        void slotStop();
        // ɾ��
        void slotDelete();
        // ˢ��
        void slotRefresh();
        // �����ѯ
        void slotTaskQuery();
        // ����ֹͣ
        void slotTaskStop();
        // ��־��¼
        void slotLogRecord();
        // Init
        void slotInit();

private:
    void readCheckSelf(tagCheckSelf &checkSelf);
    void readFormat(quint32 state);
    void readSystemConfig(quint32 state);
    void readRecord(quint32 area, quint32 state);
    void readPlayBack(quint32 area, quint32 state);
    void readImport(quint32 area, quint32 state);
    void readExport(quint32 area, quint32 state);
    void readStop(quint32 area, quint32 state);
    void readDelete(quint32 area, quint32 state);
    void readRefresh(tagAreaFileInfos &fileInfos);
    void readTaskQuery(list<tagTaskInfo>& lstTaskInfo);
    void readTaskStop(qint32 tasktype, qint32 taskrespond);

    void logRecord(QString sText);

private:
    tagAreaProperties       m_areaProperties;

private:
    QAction                 *m_pActCheckSelf;   // �Լ�
    QAction                 *m_pActFormat;      // ��ʽ��
    QAction                 *m_pActIPSetting;   // IP����
    QAction                 *m_pActSystemConfig;//ϵͳ����
    QAction                 *m_pActAbout;       // ����
    QAction                 *m_pActImport;      // ����
    QAction                 *m_pActExport;      // ����
    QAction                 *m_pActRecord;      // ��¼
    QAction                 *m_pActDelete;      // ɾ��
    QAction                 *m_pActRefresh;     // ˢ��
    QAction                 *m_pActPlayBack;    // �ط�
    QAction                 *m_pActStop;        // ֹͣ
    QMenu                   *m_menuSystemControl;

    QTcpSocket              *m_pTcpSocket;      // 

    QTableWidget            *m_pLDDataWgt1;     // �״�����_1
    QTableWidget            *m_pLDDataWgt2;     // �״�����_2
    QTableWidget            *m_pGDDataWgt1;     // �������_1
    QTableWidget            *m_pGDDataWgt2;     // �������_2
    QTableWidget            *m_pHHDataWgt;      // �������

    QTableWidget            *m_pTaskWgt;        // �����б��
    QTableWidget            *m_pLogWgt;         // ��־�����

    QtTreePropertyBrowser   *m_pPropertyWgt1;   // ���̿������
    QFrame                  *m_pPropertyWgt2;   // ��������

    QSplitter               *m_pSplitter;
    QLabel                  *m_pStateLabel;     // ״̬

    QtGroupPropertyManager  *m_groupManager;
    QtStringPropertyManager *m_stringManager;
    QtDoublePropertyManager *m_doubleManager;
    DecoratedDoublePropertyManager *m_ddoubleManager;
    QtIntPropertyManager    *m_intManager;
    QtEnumPropertyManager   *m_enumManager;
};

#endif // HOSTMACHINE_H
