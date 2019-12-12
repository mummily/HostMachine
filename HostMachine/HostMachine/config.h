#pragma once

#include <QVariantMap>

class Config
{
public:
    Config(const QString &fileName);
    ~Config();

    QString readString(const QString &key, const QString &default = "");
    bool readBool(const QString &key, bool default = false);
    int readInt(const QString &key, int default = 0);

private:
    bool open(const QString &fileName);

private:
    QString m_fileName;
    QVariantMap m_cache;
};

