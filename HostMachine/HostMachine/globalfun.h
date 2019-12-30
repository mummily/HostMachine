#pragma once
#include "qglobal.h"
#include <QDateTime>

class CGlobalFun
{
public:
    CGlobalFun(void);
    ~CGlobalFun(void);

    static QString formatSize(qint64 oldBytes);
    static void formatSize(qint64 oldBytes, float& newBytes, QString& sUnit);
    static QString formatElapsedTime(qint64 elapsed);
    static qint64 Dt2Int(QDateTime dt);
    static QDateTime Int2Dt(qint64 datetime);
    static QString formatVersionNo(qint32 versionNo);
    static QString formatChannel(qint32 channel);
};