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
    {
        return false;
    }

    QByteArray allData = file.readAll();
    file.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(allData, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        return false;
    }

    QJsonObject root = jsonDoc.object();
    m_cache = root.toVariantMap();

    return true;
}

void Config::sync()
{
    QJsonObject root = QJsonObject::fromVariantMap(m_cache);
    QJsonDocument jsonDoc(root);
    QByteArray data = jsonDoc.toJson(QJsonDocument::Compact);
    QFile file(m_fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(data);
        file.close();
    }
}

void Config::write(const QString &key, const QVariant &value)
{
    m_cache.insert(key, value);
}

QString Config::readString(const QString &key, const QString &default)
{
    if (m_cache.contains(key))
    {
        return m_cache.value(key).toString();
    }

    return default;
}

bool Config::readBool(const QString &key, bool default)
{
    if (m_cache.contains(key))
    {
        return m_cache.value(key).toBool();
    }

    return default;
}

int Config::readInt(const QString &key, int default)
{
    if (m_cache.contains(key))
    {
        return m_cache.value(key).toInt();
    }

    return default;
}