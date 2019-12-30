#pragma once
#include <QString>
#include <QDateTime>
#include <QDataStream>
#include <memory>

using namespace std;

const int c_uRefreshFileNum = 8;
const int c_uTaskQueryNum = 14;
const int c_uProgressBarUpdateInterval = 100;
const int c_uRequestEndTag = 0x5a5a5a5a;

const int c_bSizeMax = 1024;
const int c_kSizeMax = c_bSizeMax * 1024;
const int c_mSizeMax = c_kSizeMax * 1024;
const qint64 c_gSizeMax = c_mSizeMax * 1024;
const int c_bufferSize = 4 * c_bSizeMax;

// 刷新 - 文件信息
struct tagAreaFileInfo
{
    quint32 fileno;     // 文件编号
    QString sFileName;  // 文件名称
    quint32 filesize;     // 文件大小
    QDateTime datetime; // 创建时间
};

// 刷新 - 文件信息
struct tagAreaFileInfos
{
    quint32 areano;     // 分区号
    quint32 fileno;     // 起始文件编号
    quint32 filenum;    // 文件数
    list<shared_ptr<tagAreaFileInfo>> lstFileInfo;
};