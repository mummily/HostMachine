#pragma once
#include "qglobal.h"

class CGlobalFun
{
public:
    CGlobalFun(void);
    ~CGlobalFun(void);

    static QString formatSize(qint64 oldBytes);
    static QString formatElapsedTime(qint64 elapsed);
};