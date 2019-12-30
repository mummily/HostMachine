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

// ˢ�� - �ļ���Ϣ
struct tagAreaFileInfo
{
    quint32 fileno;     // �ļ����
    QString sFileName;  // �ļ�����
    quint32 filesize;     // �ļ���С
    QDateTime datetime; // ����ʱ��
};

// ˢ�� - �ļ���Ϣ
struct tagAreaFileInfos
{
    quint32 areano;     // ������
    quint32 fileno;     // ��ʼ�ļ����
    quint32 filenum;    // �ļ���
    list<shared_ptr<tagAreaFileInfo>> lstFileInfo;
};