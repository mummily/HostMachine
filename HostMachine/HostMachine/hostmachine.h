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
    QAction                 *m_pActCheckSelf;   // 自检
    QAction                 *m_pActFormat;      // 格式化
    QAction                 *m_pActIPSetting;   // IP设置
    QAction                 *m_pActSystemSetting;//系统设置
    QAction                 *m_pActAbout;       // 关于
    QAction                 *m_pActImport;      // 导入
    QAction                 *m_pActExport;      // 导出
    QAction                 *m_pActRecord;      // 记录
    QAction                 *m_pActDelete;      // 删除
    QAction                 *m_pActRefresh;     // 刷新
    QAction                 *m_pActPlayback;    // 回放
    QAction                 *m_pActStop;        // 停止
    QMenu                   *m_menuSystemControl;

    QTcpSocket              *m_pTcpSocket;      // 
    QTcpServer              *m_pTcpServer;      // 

    QTableWidget            *m_pLDDataWgt1;     // 雷达数据_1
    QTableWidget            *m_pLDDataWgt2;     // 雷达数据_2
    QTableWidget            *m_pGDDataWgt1;     // 光电数据_1
    QTableWidget            *m_pGDDataWgt2;     // 光电数据_2
    QTableWidget            *m_pHHDataWgt;      // 混合数据

    QTableWidget            *m_pTaskWgt;        // 任务列表框
    QTableWidget            *m_pLogWgt;         // 日志输出框

    QtTreePropertyBrowser   *m_pPropertyWgt1;   // 磁盘控制面板
    QFrame                  *m_pPropertyWgt2;   // 基本参数

    QSplitter               *m_pSplitter;
    QLabel                  *m_pStateLabel;     // 状态
};

#endif // HOSTMACHINE_H
