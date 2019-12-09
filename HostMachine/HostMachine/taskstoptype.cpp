#include "taskstoptype.h"
#include <QApplication>

static const char *c_sTaskType = "TaskStopType";
static const char *c_sTaskType1 = QT_TRANSLATE_NOOP("TaskStopType", "任务类型1");

TaskStopType::TaskStopType(void)
{
    // 任务类型 - 任务名称
    m_mapTaskType[0x01] = qApp->translate(c_sTaskType, c_sTaskType1);
}


TaskStopType::~TaskStopType(void)
{
}
