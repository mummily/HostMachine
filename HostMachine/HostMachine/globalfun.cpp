#include "globalfun.h"
#include "common.h"
#include <QString>

CGlobalFun::CGlobalFun(void)
{
}


CGlobalFun::~CGlobalFun(void)
{
}

void CGlobalFun::formatSize(qint64 oldBytes, float& newBytes, QString& sUnit)
{
    newBytes = oldBytes;
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
