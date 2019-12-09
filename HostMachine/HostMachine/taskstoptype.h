#pragma once
#include "QMap"

class TaskStopType
{
public:
    TaskStopType(void);
    ~TaskStopType(void);

public:
    QMap<quint32, QString>  m_mapTaskType;
};

