#pragma once
#include <QString>

const quint16 c_uCommandPort = 6178;
const quint16 c_uDataPort = 6188;

const int c_bSizeMax = 1024;
const int c_kSizeMax = c_bSizeMax * 1024;
const int c_mSizeMax = c_kSizeMax * 1024;
const qint64 c_gSizeMax = c_mSizeMax * 1024;
const int c_bufferSize = 4 * c_bSizeMax;

const QString c_sFileHead= "{2585E781-1C60-416E-9A18-CC7ACD2522AF}";
const QString c_sFileTail= "{FFEE539A-6E91-4461-AD05-8B5F21CAF18D}";