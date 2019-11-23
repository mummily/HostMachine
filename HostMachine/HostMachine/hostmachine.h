#ifndef HOSTMACHINE_H
#define HOSTMACHINE_H

#include <QtWidgets/QMainWindow>

using namespace std;
#include "common.h"
#include "tasktype.h"
#include "QNetworkReply"

class QtProperty;

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

// ͨ������
struct tagChannelProperty
{
    QtProperty* pItem1;
    QtProperty* pItem2;
    QtProperty* pItem3;

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
class MWFileList;
class QFile;
class QNetworkReply;
class DataSocket;
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
    void initData();

    void initTaskWgt();
    void initPropertyWgt();

private:
    void reallyCheckSelf();
    void reallyRefresh();

    private slots:
        // TCP
        void connectedCmd();
        void disconnectCmd();
        void readyReadCmd();
        void errorCmd();
        void readContent();
        void replyFinished(QNetworkReply* pNetworkReply);
        void loadError(QNetworkReply::NetworkError code);

        void connectedData();
        void disconnectData();
        void readyReadData();
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
        void slotPlayBack(quint32 fileno, quint32 type, quint32 prftime, quint32 datanum, quint32 prf, quint32 cpi);
        // ����
        void slotImport();
        // ����
        void slotExport();
        // ֹͣ
        void slotStop();
        // ɾ��
        void slotDelete(QList<quint32> fileNos);
        // ˢ��
        void slotRefresh();

        // Init
        void slotInit();
        // Tab Changed
        void slotTabChanged(int index);
        void slotUpdateProcess(QString fileName, float buffer, float total);

private:
    void readCheckSelf();
    void readFormat(quint32 state);
    void readSystemConfig(quint32 choice, quint32 state);
    void readTaskQuery(list<tagTaskInfo>& lstTaskInfo);
private:
    tagAreaProperties       m_areaProperties;
    shared_ptr<tagCheckSelf> m_spcheckSelf;
    shared_ptr<TaskType>    m_spTaskType;
    QString                 m_sAddr;

private:
    QAction                 *m_pActCheckSelf;   // �Լ�
    QAction                 *m_pActFormat;      // ��ʽ��
    QAction                 *m_pActIPSetting;   // IP����
    QAction                 *m_pActSystemConfig;//ϵͳ����
    QAction                 *m_pActAbout;       // ����
    QMenu                   *m_pMenuSystemControl;

    QTcpSocket              *m_pCmdSocket;      // ����Socket
    DataSocket              *m_pDataSocket;     // ����Socket
    QNetworkReply           *m_pNetworkReply;

    MWFileList              *m_pLDOriginalWgt;  // �״�ԭʼ���ݷ���
    MWFileList              *m_pLDResultWgt;    // �״������ݷ���
    MWFileList              *m_pGDImgWgt;       // ���ͼƬ����
    MWFileList              *m_pGDVidioWgt;     // �����Ƶ����
    MWFileList              *m_pHHDataWgt;      // ������ݷ���

    QTableWidget            *m_pTaskWgt;        // �����б��

    QtTreePropertyBrowser   *m_pPropertyWgt;   // ���̿������

    QTabWidget              *m_pTabWgt;
    QSplitter               *m_pSplitter;
    QLabel                  *m_pIPLabel;        // ״̬
    QLabel                  *m_pCmdLabel;       // ״̬
    QLabel                  *m_pDataLabel;      // ״̬
    QFile                   *m_pFile;
    QFile                   *m_pLog;

    QtGroupPropertyManager  *m_groupManager;
    QtStringPropertyManager *m_stringManager;
    QtDoublePropertyManager *m_doubleManager;
    DecoratedDoublePropertyManager *m_ddoubleManager;
    QtIntPropertyManager    *m_intManager;
    QtEnumPropertyManager   *m_enumManager;
};

#endif // HOSTMACHINE_H
