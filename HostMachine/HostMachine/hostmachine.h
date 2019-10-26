#ifndef HOSTMACHINE_H
#define HOSTMACHINE_H

#include <QtWidgets/QMainWindow>

class QTableWidget;
class QTabWidget;
class QSplitter;
class QtTreePropertyBrowser;
class QFrame;
class QLabel;
class QTcpSocket;
class QTcpServer;
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
        void slotIPSetting();

private:
    QAction                 *m_pActCheckSelf;   // �Լ�
    QAction                 *m_pActFormat;      // ��ʽ��
    QAction                 *m_pActIPSetting;   // IP����
    QAction                 *m_pActSystemSetting;//ϵͳ����
    QAction                 *m_pActAbout;       // ����
    QAction                 *m_pActImport;      // ����
    QAction                 *m_pActExport;      // ����
    QAction                 *m_pActRecord;      // ��¼
    QAction                 *m_pActDelete;      // ɾ��
    QAction                 *m_pActRefresh;     // ˢ��
    QAction                 *m_pActPlayback;    // �ط�
    QAction                 *m_pActStop;        // ֹͣ
    QMenu                   *m_menuSystemControl;

    QTcpSocket              *m_pTcpSocket;      // 
    QTcpServer              *m_pTcpServer;      // 

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
};

#endif // HOSTMACHINE_H
