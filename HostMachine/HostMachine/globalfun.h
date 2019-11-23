#pragma once
#include "qglobal.h"
class CGlobalFun
{
public:
    CGlobalFun(void);
    ~CGlobalFun(void);

    static void formatSize(qint64 oldBytes, float& newBytes, QString& sUnit);
};

