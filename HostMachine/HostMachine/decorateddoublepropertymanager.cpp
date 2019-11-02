#include "decorateddoublepropertymanager.h"

DecoratedDoublePropertyManager::DecoratedDoublePropertyManager(QObject *parent)
    : QtDoublePropertyManager(parent)
{
}

DecoratedDoublePropertyManager::~DecoratedDoublePropertyManager()
{

}

void DecoratedDoublePropertyManager::setSuffix(QtProperty *property, const QString &suffix)
{
    propertyToData[property] = suffix;

    emit propertyChanged(property);
}

QString DecoratedDoublePropertyManager::valueText(const QtProperty *property) const
{
    QString text = QtDoublePropertyManager::valueText(property);
    if (!propertyToData.contains(property))
        return text;

    QString suffix = propertyToData[property];
    text = text + suffix;

    return text;
}