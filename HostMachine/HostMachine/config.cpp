#include "Config.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

Config::Config(const QString &fileName)
    : m_fileName(fileName)
{
    bool bOk = open(fileName);
    Q_ASSERT(bOk);
}

Config::~Config()
{
}

bool Config::open(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QByteArray allData = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(allData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
        return false;

    QJsonObject root = jsonDoc.object();
    m_cache = root.toVariantMap();

    return true;
}

QString Config::readString(const QString &key, const QString &default)
{
    if (m_cache.contains(key))
        return m_cache.value(key).toString();

    return default;
}

bool Config::readBool(const QString &key, bool default)
{
    if (m_cache.contains(key))
        return m_cache.value(key).toBool();

    return default;
}

int Config::readInt(const QString &key, int default)
{
    if (m_cache.contains(key))
        return m_cache.value(key).toInt();

    return default;
}