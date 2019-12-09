#include "globalfun.h"
#include "common.h"
#include <QString>

CGlobalFun::CGlobalFun(void)
{
}


CGlobalFun::~CGlobalFun(void)
{
}

void CGlobalFun::formatSize(qint64 oldBytes, qint64& newBytes, QString& sUnit)
{
    newBytes= oldBytes;
    sUnit = "B";

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
}

QString CGlobalFun::formatSize(qint64 oldBytes)
{
    qint64 newBytes = 0;
    QString sUnit = "";
    formatSize(oldBytes, newBytes, sUnit);
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

qint64 CGlobalFun::Dt2Int(QDateTime dt)
{
    qint64 datetime = 0x00;
    qint64 year = dt.date().year() - 2000;
    qint64 month = dt.date().month();
    qint64 day = dt.date().day();

    qint64 hour = dt.time().hour();
    qint64 minute = dt.time().minute();
    qint64 second = dt.time().second();

    datetime += year << 8*6;
    datetime += month << 8*5;
    datetime += day << 8*4;
    datetime += hour << 8*3;
    datetime += minute << 8*2;
    datetime += second << 8*1;

    return datetime;
}

QDateTime CGlobalFun::Int2Dt(qint64 datetime)
{
    QString sDateTime = "20";
    // year
    {
        qint64 year  = datetime;
        year = year << 8*1;
        year = year >> 8*7;
        sDateTime += QString::number(year);
    }
    // month
    {
        qint64 month  = datetime;
        month  = month << 8*2;
        month  = month >> 8*7;
        sDateTime += "-";
        sDateTime += QString::number(month);
    }
    // day
    {
        qint64 day  = datetime;
        day  = day << 8*3;
        day  = day >> 8*7;
        sDateTime += "-";
        sDateTime += QString::number(day);
    }
    // hour
    {
        qint64 hour  = datetime;
        hour  = hour << 8*4;
        hour  = hour >> 8*7;
        sDateTime += " ";
        sDateTime += QString::number(hour);
    }
    // minute
    {
        qint64 minute  = datetime;
        minute  = minute << 8*5;
        minute  = minute >> 8*7;
        sDateTime += ":";
        sDateTime += QString::number(minute);
    }
    // second
    {
        qint64 second  = datetime;
        second  = second << 8*6;
        second  = second >> 8*7;
        sDateTime += ":";
        sDateTime += QString::number(second);
    }

    return QDateTime::fromString(sDateTime, "yyyy-MM-dd hh:mm:ss");
}