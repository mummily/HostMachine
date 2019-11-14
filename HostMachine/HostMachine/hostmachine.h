#ifndef HOSTMACHINE_H
#define HOSTMACHINE_H

#include <QtWidgets/QMainWindow>

using namespace std;
#include "constdef.h"

class QtProperty;

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

    void initTaskWgt();
    void initPropertyWgt();

    private slots:
        // TCP
        void connectedCmd();
        void disconnectCmd();
        void readyReadCmd();
        void errorCmd();

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
        void slotLogRecord();
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

private:
    void readCheckSelf();
    void readFormat(quint32 state);
    void readSystemConfig(quint32 choice, quint32 state);
    void readTaskQuery(list<tagTaskInfo>& lstTaskInfo);
    void logRecord(QString sText);

private:
    tagAreaProperties       m_areaProperties;
    shared_ptr<tagCheckSelf> m_spcheckSelf;

private:
    QAction                 *m_pActCheckSelf;   // �Լ�
    QAction                 *m_pActFormat;      // ��ʽ��
    QAction                 *m_pActIPSetting;   // IP����
    QAction                 *m_pActSystemConfig;//ϵͳ����
    QAction                 *m_pActAbout;       // ����
    QMenu                   *m_pMenuSystemControl;

    QTcpSocket              *m_pCmdSocket;      // ����Socket
    QTcpSocket              *m_pDataSocket;     // ����Socket

    MWFileList              *m_pLDOriginalWgt;  // �״�ԭʼ���ݷ���
    MWFileList              *m_pLDResultWgt;    // �״������ݷ���
    MWFileList              *m_pGDImgWgt;       // ���ͼƬ����
    MWFileList              *m_pGDVidioWgt;     // �����Ƶ����
    MWFileList              *m_pHHDataWgt;      // ������ݷ���

    QTableWidget            *m_pTaskWgt;        // �����б��

    QtTreePropertyBrowser   *m_pPropertyWgt;   // ���̿������

    QTabWidget              *m_pTabWgt;
    QSplitter               *m_pSplitter;
    QLabel                  *m_pCmdLabel;       // ״̬
    QLabel                  *m_pDataLabel;      // ״̬

    QtGroupPropertyManager  *m_groupManager;
    QtStringPropertyManager *m_stringManager;
    QtDoublePropertyManager *m_doubleManager;
    DecoratedDoublePropertyManager *m_ddoubleManager;
    QtIntPropertyManager    *m_intManager;
    QtEnumPropertyManager   *m_enumManager;
};

#endif // HOSTMACHINE_H
