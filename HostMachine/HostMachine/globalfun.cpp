#include "globalfun.h"
#include "common.h"
#include <QString>

CGlobalFun::CGlobalFun(void)
{
}


CGlobalFun::~CGlobalFun(void)
{
}

/**************************************************
*功能       :   转换文件大小
*创建者     :   wb
*创建日期   :   2019.12.09
*描述       :   
***************************************************/
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

/**************************************************
*功能       :   转换文件大小
*创建者     :   wb
*创建日期   :   2019.12.09
*描述       :   
***************************************************/
QString CGlobalFun::formatSize(qint64 oldBytes)
{
    qint64 newBytes = 0;
    QString sUnit = "";
    formatSize(oldBytes, newBytes, sUnit);
    return QString("%0 %1").arg(newBytes).arg(sUnit);
}

/**************************************************
*功能       :   转换用时
*创建者     :   wb
*创建日期   :   2019.12.09
*描述       :   
***************************************************/
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

/**************************************************
*功能       :   时间格式转换
*创建者     :   wb
*创建日期   :   2019.12.09
*描述       :   
***************************************************/
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

/**************************************************
*功能       :   时间格式转换
*创建者     :   wb
*创建日期   :   2019.12.09
*描述       :   
***************************************************/
QDateTime CGlobalFun::Int2Dt(qint64 datetime)
{
    // year
    qint64 year  = datetime;
    year = year << 8*1;
    year = year >> 8*7;

    // month
    qint64 month  = datetime;
    month  = month << 8*2;
    month  = month >> 8*7;

    // day
    qint64 day  = datetime;
    day  = day << 8*3;
    day  = day >> 8*7;

    // hour
    qint64 hour  = datetime;
    hour  = hour << 8*4;
    hour  = hour >> 8*7;

    // minute
    qint64 minute  = datetime;
    minute  = minute << 8*5;
    minute  = minute >> 8*7;

    // second
    qint64 second  = datetime;
    second  = second << 8*6;
    second  = second >> 8*7;

    return QDateTime(QDate(2000 + year, month, day), QTime(hour, minute, second));
}

/**************************************************
*功能       :   版本号
*创建者     :   wb
*创建日期   :   2019.12.09
*描述       :   
***************************************************/
QString CGlobalFun::formatVersionNo(qint32 versionNo)
{
    QString sVersionNo = "";

    // major
    {
        qint32 major  = versionNo;
        major  = major << 8*1;
        major  = major >> 8*3;
        sVersionNo = QString::number(major);
    }
    // middle
    {
        qint32 middle  = versionNo;
        middle  = middle << 8*2;
        middle  = middle >> 8*3;
        sVersionNo += ".";
        sVersionNo += QString::number(middle);
    }
    // minor
    {
        qint32 minor  = versionNo;
        minor  = minor << 8*3;
        minor  = minor >> 8*3;
        sVersionNo += ".";
        sVersionNo += QString::number(minor);
    }

    return sVersionNo;
}

/**************************************************
*功能       :   通道
*创建者     :   wb
*创建日期   :   2019.12.09
*描述       :   
***************************************************/
QString CGlobalFun::formatChannel(qint32 channel)
{
    QString sChannel = "";
    if (channel & 0x01)
        sChannel = "1";
    if (channel & 0x02)
        sChannel = (sChannel == "") ? "2" : (sChannel + "/2");
    if (channel & 0x04)
        sChannel = (sChannel == "") ? "3" : (sChannel + "/3");
    if (channel & 0x08)
        sChannel = (sChannel == "") ? "4" : (sChannel + "/4");
    if (channel & 0x10)
        sChannel = (sChannel == "") ? "5" : (sChannel + "/5");
    if (channel & 0x20)
        sChannel = (sChannel == "") ? "6" : (sChannel + "/6");
    if (channel & 0x40)
        sChannel = (sChannel == "") ? "7" : (sChannel + "/7");
    if (channel & 0x80)
        sChannel = (sChannel == "") ? "8" : (sChannel + "/8");

    return sChannel;
}
