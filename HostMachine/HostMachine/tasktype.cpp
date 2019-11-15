#include "TaskType.h"
#include <QApplication>

static const char *c_sTaskType = "TaskType";
static const char *c_sSystemConfig = QT_TRANSLATE_NOOP("TaskType", "系统配置");
static const char *c_sSystemOperation = QT_TRANSLATE_NOOP("TaskType", "系统操作");

static const char *c_sCheckSelf = QT_TRANSLATE_NOOP("TaskType", "自检");
static const char *c_sFormat = QT_TRANSLATE_NOOP("TaskType", "格式化");
static const char *c_sImport = QT_TRANSLATE_NOOP("TaskType", "导入");
static const char *c_sExport = QT_TRANSLATE_NOOP("TaskType", "导出");
static const char *c_sRecord = QT_TRANSLATE_NOOP("TaskType", "记录");
static const char *c_sDelete = QT_TRANSLATE_NOOP("TaskType", "删除");
static const char *c_sRefresh = QT_TRANSLATE_NOOP("TaskType", "刷新");
static const char *c_sPlayBack = QT_TRANSLATE_NOOP("TaskType", "回放");
static const char *c_sStop = QT_TRANSLATE_NOOP("TaskType", "停止");
static const char *c_sTaskStop = QT_TRANSLATE_NOOP("TaskType", "任务停止");
static const char *c_sTaskQuery = QT_TRANSLATE_NOOP("TaskType", "任务查询");

TaskType::TaskType(void)
{
    // 任务类型 - 任务名称
    m_mapClientTaskType[CS_CheckSelf] = qApp->translate(c_sTaskType, c_sCheckSelf);
    m_mapClientTaskType[CS_Format] = qApp->translate(c_sTaskType, c_sFormat);
    m_mapClientTaskType[CS_SystemConfig] = qApp->translate(c_sTaskType, c_sSystemConfig);
    m_mapClientTaskType[CS_Record] = qApp->translate(c_sTaskType, c_sRecord);
    m_mapClientTaskType[CS_PlayBack] = qApp->translate(c_sTaskType, c_sPlayBack);
    m_mapClientTaskType[CS_Import] = qApp->translate(c_sTaskType, c_sImport);
    m_mapClientTaskType[CS_Export] = qApp->translate(c_sTaskType, c_sExport);
    // m_mapClientTaskType[CS_Stop] = qApp->translate(c_sTaskType, c_sStop);
    m_mapClientTaskType[CS_Delete] = qApp->translate(c_sTaskType, c_sDelete);
    m_mapClientTaskType[CS_Refresh] = qApp->translate(c_sTaskType, c_sRefresh);
    m_mapClientTaskType[CS_TaskQuery] = qApp->translate(c_sTaskType, c_sTaskQuery);
    m_mapClientTaskType[CS_TaskStop] = qApp->translate(c_sTaskType, c_sTaskStop);

    // 客户端任务类型 - 服务端任务类型
    m_mapClientServerTaskType[CS_CheckSelf] = SC_CheckSelf;
    m_mapClientServerTaskType[CS_Format] = SC_Format;
    m_mapClientServerTaskType[CS_SystemConfig] = SC_SystemConfig;
    m_mapClientServerTaskType[CS_Record] = SC_Record;
    m_mapClientServerTaskType[CS_PlayBack] = SC_PlayBack;
    m_mapClientServerTaskType[CS_Import] = SC_Import;
    m_mapClientServerTaskType[CS_Export] = SC_Export;
    // m_mapClientServerTaskType[CS_Stop] = SC_Stop;
    m_mapClientServerTaskType[CS_Delete] = SC_Delete;
    m_mapClientServerTaskType[CS_Refresh] = SC_Refresh;
    m_mapClientServerTaskType[CS_TaskQuery] = SC_TaskQuery;
    m_mapClientServerTaskType[CS_TaskStop] = SC_TaskStop;
}


TaskType::~TaskType(void)
{
}
