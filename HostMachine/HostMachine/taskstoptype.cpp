#include "taskstoptype.h"
#include <QApplication>

static const char *c_sTaskType = "TaskStopType";
static const char *c_sTaskType1 = QT_TRANSLATE_NOOP("TaskStopType", "��������1");

TaskStopType::TaskStopType(void)
{
    // �������� - ��������
    m_mapTaskType[0x01] = qApp->translate(c_sTaskType, c_sTaskType1);
}


TaskStopType::~TaskStopType(void)
{
}
