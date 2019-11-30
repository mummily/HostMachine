#include "globalfun.h"
#include "common.h"
#include <QString>

CGlobalFun::CGlobalFun(void)
{
}


CGlobalFun::~CGlobalFun(void)
{
}

QString CGlobalFun::formatSize(qint64 oldBytes)
{
    float newBytes= oldBytes;
    QString sUnit = "B";

    if (oldBytes / c_mSizeMax > 0)
    {
        newBytes = oldBytes / (float)c_mSizeMax;
        sUnit = "GB";
    }
    else if (oldBytes / c_kSizeMax > 0)
    {
        newBytes = oldBytes / (float)c_kSizeMax;
        sUnit = "MB";
    }
    else if (oldBytes / c_bSizeMax > 0)
    {
        newBytes = oldBytes / (float)c_bSizeMax;
        sUnit = "KB";
    }

    return QString("%0 %1").arg(newBytes).arg(sUnit);
}

QString CGlobalFun::formatElapsedTime(qint64 elapsed)
{
    qint64 newElapsed = elapsed;
    if (newElapsed < 1000)
        return QString("%0 ms").arg(elapsed);

    qint64 msecond = 0;
    msecond = newElapsed % 1000;
    newElapsed /= 1000;
    if (newElapsed < 60)
        return QString("%0 s %1 ms").arg(newElapsed).arg(msecond);

    quint64 second = 0;
    second = newElapsed % 60;
    newElapsed /= 60;

    return QString("%0 min %1 s %2 ms").arg(newElapsed).arg(second).arg(msecond);
}
