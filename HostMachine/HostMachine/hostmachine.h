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

// 请求类型
enum RequestType
{
    CS_CheckSelf = 0x11,    // 自检
    CS_Format = 0xA1,       // 格式化
    CS_SystemConfig = 0xB1, // 系统配置
    CS_Record = 0x21,       // 记录
    CS_PlayBack = 0x31,     // 回放
    CS_Import = 0x41,       // 导入
    CS_Export = 0x51,       // 导出
    CS_Stop = 0x61,         // 停止
    CS_Delete = 0x71,       // 删除
    CS_Refresh = 0x81,      // 刷新
    CS_TaskQuery = 0x91,    // 任务查询
    CS_TaskStop = 0xC1,     // 任务停止
};

// 应答类型
enum RespondType
{
    SC_CheckSelf = 0x1011,      // 自检
    SC_Format = 0x10A1,         // 格式化
    SC_SystemConfig = 0x10B1,   // 系统配置
    SC_Record = 0x1021,         // 记录
    SC_PlayBack = 0x1031,       // 回放
    SC_Import = 0x1041,         // 导入
    SC_Export = 0x1051,         // 导出
    SC_Stop = 0x1061,           // 停止
    SC_Delete = 0x1071,         // 删除
    SC_Refresh = 0x1081,        // 刷新
    SC_TaskQuery = 0x1091,      // 任务查询
    SC_TaskStop = 0x10C1,       // 任务停止
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
            >> bandwidth
            >> hardversion
            >> fpgaversion;
    }
};

// 自检应答-自检信息
struct tagCheckSelf
{
    shared_ptr<tagAreaInfo> areaInfo0, areaInfo1, areaInfo2, areaInfo3, areaInfo4;
    shared_ptr<tagChannelInfo> channelInfo;

    tagCheckSelf()
    {

    }
};

// 分区属性
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
        // IP设置
        void slotIPSetting();
        // 自检
        void slotCheckSelf();
        // 格式化
        void slotFormat();
        // 系统配置
        void slotSystemConfig();
        // 记录
        void slotRecord();
        // 回放
        void slotPlayBack();
        // 导入
        void slotImport();
        // 导出
        void slotExport();
        // 停止
        void slotStop();
        // 删除
        void slotDelete();
        // 刷新
        void slotRefresh();
        // 任务查询
        void slotTaskQuery();
        // 任务停止
        void slotTaskStop();
        // 日志记录
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
    QAction                 *m_pActCheckSelf;   // 自检
    QAction                 *m_pActFormat;      // 格式化
    QAction                 *m_pActIPSetting;   // IP设置
    QAction                 *m_pActSystemConfig;//系统设置
    QAction                 *m_pActAbout;       // 关于
    QAction                 *m_pActImport;      // 导入
    QAction                 *m_pActExport;      // 导出
    QAction                 *m_pActRecord;      // 记录
    QAction                 *m_pActDelete;      // 删除
    QAction                 *m_pActRefresh;     // 刷新
    QAction                 *m_pActPlayBack;    // 回放
    QAction                 *m_pActStop;        // 停止
    QMenu                   *m_menuSystemControl;

    QTcpSocket              *m_pTcpSocket;      // 

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

    QtGroupPropertyManager  *m_groupManager;
    QtStringPropertyManager *m_stringManager;
    QtDoublePropertyManager *m_doubleManager;
    DecoratedDoublePropertyManager *m_ddoubleManager;
    QtIntPropertyManager    *m_intManager;
    QtEnumPropertyManager   *m_enumManager;
};

#endif // HOSTMACHINE_H
