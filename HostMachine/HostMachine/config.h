#pragma once

#include <QVariantMap>

class Config
{
public:
    Config(const QString &fileName);
    ~Config();

    // ¶Á
    QString readString(const QString &key, const QString &default = "");
    bool readBool(const QString &key, bool default = false);
    int readInt(const QString &key, int default = 0);

    // Ð´
    void write(const QString &key, const QVariant& value);
    void sync();
private:
    bool open(const QString &fileName);

private:
    QString m_fileName;
    QVariantMap m_cache;
};

