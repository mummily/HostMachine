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
        // IP设置
        void slotIPSetting();
        // 自检
        void slotCheckSelf();
        // 格式化
        void slotFormat();
        // 系统配置
        void slotSystemConfig();
        // 任务查询
        void slotTaskQuery();
        // 日志记录
        void slotLogRecord();
        // 记录
        void slotRecord();
        // 回放
        void slotPlayBack(quint32 fileno, quint32 type, quint32 prftime, quint32 datanum, quint32 prf, quint32 cpi);
        // 导入
        void slotImport();
        // 导出
        void slotExport();
        // 停止
        void slotStop();
        // 删除
        void slotDelete(QList<quint32> fileNos);
        // 刷新
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
    QAction                 *m_pActCheckSelf;   // 自检
    QAction                 *m_pActFormat;      // 格式化
    QAction                 *m_pActIPSetting;   // IP设置
    QAction                 *m_pActSystemConfig;//系统设置
    QAction                 *m_pActAbout;       // 关于
    QMenu                   *m_pMenuSystemControl;

    QTcpSocket              *m_pCmdSocket;      // 命令Socket
    QTcpSocket              *m_pDataSocket;     // 数据Socket

    MWFileList              *m_pLDOriginalWgt;  // 雷达原始数据分区
    MWFileList              *m_pLDResultWgt;    // 雷达结果数据分区
    MWFileList              *m_pGDImgWgt;       // 光电图片分区
    MWFileList              *m_pGDVidioWgt;     // 光电视频分区
    MWFileList              *m_pHHDataWgt;      // 混合数据分区

    QTableWidget            *m_pTaskWgt;        // 任务列表框

    QtTreePropertyBrowser   *m_pPropertyWgt;   // 磁盘控制面板

    QTabWidget              *m_pTabWgt;
    QSplitter               *m_pSplitter;
    QLabel                  *m_pCmdLabel;       // 状态
    QLabel                  *m_pDataLabel;      // 状态

    QtGroupPropertyManager  *m_groupManager;
    QtStringPropertyManager *m_stringManager;
    QtDoublePropertyManager *m_doubleManager;
    DecoratedDoublePropertyManager *m_ddoubleManager;
    QtIntPropertyManager    *m_intManager;
    QtEnumPropertyManager   *m_enumManager;
};

#endif // HOSTMACHINE_H
