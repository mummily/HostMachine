#pragma once
#include "qglobal.h"

class CGlobalFun
{
public:
    CGlobalFun(void);
    ~CGlobalFun(void);

    static QString formatSize(qint64 oldBytes);
    static void formatSize(qint64 oldBytes, qint64& newBytes, QString& sUnit);
    static QString formatElapsedTime(qint64 elapsed);
};