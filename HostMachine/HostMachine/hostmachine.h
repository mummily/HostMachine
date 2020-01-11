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

// 分区属性
struct tagAreaProperty
{
    QtProperty *pItem1, *pItem2, *pItem3, *pItem4, *pItem5;
    tagAreaProperty()
    {
    }
};

// 通道属性
struct tagChannelProperty
{
    QtProperty *pItem1, *pItem2, *pItem3;
    tagChannelProperty()
    {
    }
};

// 版本号属性
struct tagVersionProperty
{
    QtProperty *pItem1, *pItem2;
    tagVersionProperty()
    {
    }
};

// 界面显示：磁盘控制面板
struct tagAreaProperties
{
    shared_ptr<tagAreaProperty> ldProperty1;    // 原始数据分区
    shared_ptr<tagAreaProperty> ldProperty2;    // 雷达结果分区
    shared_ptr<tagAreaProperty> gdProperty1;    // 光电图片分区
    shared_ptr<tagAreaProperty> gdProperty2;    // 光电视频分区
    shared_ptr<tagAreaProperty> hhProperty;     // 混合数据分区
    shared_ptr<tagChannelProperty> channelProperty; // 参数信息
    shared_ptr<tagVersionProperty> versionProperty; // 版本号信息

    tagAreaProperties()
    {
    }
};

// 任务查询应答-任务信息
struct tagTaskInfo
{
    quint32 flag; // 标记 1-有效任务 0-无效任务
    quint32 area; // 分区 0-0分区 1-1分区
    quint32 type; // 任务类型 0-数据0 1-数据1 2-导入导出 3-回放
    quint32 finishedsize; // 任务已完成大小
    quint32 speed; // 任务速度
    quint32 percent; // 任务进度百分比
    quint32 state; // 任务状态 0-等待执行 1-执行中 2-已完成

    tagTaskInfo()
    {
    }
};

// 分区信息
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

// 通道信息
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

// 版本号信息
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

// 自检应答-自检信息
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
    qint32 type; // 0-记录 1-导入导出
    qint32 areano; // 分区
    qint64 filesize; // 文件总大小
    QDateTime dtStart; // 任务开始时间
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
        void slotLogRecord(QString sText);
        void slotLogRecordAct();
        // 记录
        void slotRecord();
        // 回放
        void slotPlayBack();
        // 导入
        void slotImport();
        void slotForeachImport();
        // 导出
        void slotExport();
        void slotForeachExport();
        // 停止
        void slotStop();
        // 任务停止
        void slotTaskStop();
        // 删除
        void slotDelete();
        // 刷新
        void slotRefresh();
        // 触发任务查询
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
    QAction                             *m_pActCheckSelf;       // 自检
    QAction                             *m_pActFormat;          // 格式化
    QAction                             *m_pActIPSetting;       // IP设置
    QAction                             *m_pActSystemConfig;    //系统设置
    QAction                             *m_pActAbout;           // 关于
    QMenu                               *m_pMenuSystemControl;

    QTcpSocket                          *m_pCmdSocket;          // 命令Socket
    CDataSocket                         *m_pDataSocket;         // 数据Socket

    CMWFileList                         *m_pLDOriginalWgt;      // 雷达原始数据分区
    CMWFileList                         *m_pLDResultWgt;        // 雷达结果数据分区
    CMWFileList                         *m_pGDImgWgt;           // 光电图片分区
    CMWFileList                         *m_pGDVidioWgt;         // 光电视频分区
    CMWFileList                         *m_pHHDataWgt;          // 混合数据分区

    QTableWidget                        *m_pTaskWgt;            // 任务列表框
    QElapsedTimer                       *m_pElapsedTimer;       // 导入导出更新间隔
    QTimer                              *m_pTimer;              // 任务查询定时器
    int                                 m_nTimer;               // 任务查询无任务的次数
    quint64                             m_nProgressBarUpdateInterval;
    bool                                m_bShowTaskStop;        // 是否显示任务停止列

    QtTreePropertyBrowser               *m_pPropertyWgt;        // 磁盘控制面板

    QTabWidget                          *m_pTabWgt;
    QSplitter                           *m_pSplitter;
    QLabel                              *m_pIPLabel;            // 状态
    QLabel                              *m_pCmdLabel;           // 状态
    QLabel                              *m_pDataLabel;          // 状态
    QFile                               *m_pLog;

    QtGroupPropertyManager              *m_groupManager;
    QtStringPropertyManager             *m_stringManager;
    DecoratedDoublePropertyManager      *m_doubleManager;
    QtIntPropertyManager                *m_intManager;
    QtEnumPropertyManager               *m_enumManager;
};

#endif // HOSTMACHINE_H
