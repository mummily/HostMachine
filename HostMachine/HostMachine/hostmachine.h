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
        void slotCmdConnected();
        void slotCmdDisconnect();
        void slotCmdReadyRead();
        void slotCmdError();

        void slotDataConnected();
        void slotDataDisconnect();
        void slotDataError();

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
        // Init
        void slotInit();
        // Tab Changed
        void slotTabChanged(int index);

private:
    void readCheckSelf(tagCheckSelf &checkSelf);
    void readFormat(quint32 state);
    void readSystemConfig(quint32 state);
    void readTaskQuery(list<tagTaskInfo>& lstTaskInfo);

    void logRecord(QString sText);

private:
    tagAreaProperties       m_areaProperties;

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
