/*!
*@file      decorateddoublepropertymanager.h
*@author    wb
*@date      2019/11/03
*@remarks   double属性管理器扩展类
*@version 1.0
*/

#ifndef DECORATEDDOUBLEPROPERTYMANAGER_H
#define DECORATEDDOUBLEPROPERTYMANAGER_H
#include <QtDoublePropertyManager>

class DecoratedDoublePropertyManager : public QtDoublePropertyManager
{
    Q_OBJECT

public:
    DecoratedDoublePropertyManager(QObject *parent);
    ~DecoratedDoublePropertyManager();

    void setSuffix(QtProperty *property, const QString &suffix);

protected:
    QString valueText(const QtProperty *property) const;

private:
    QMap<const QtProperty *, QString> propertyToData;
};

#endif // DECORATEDDOUBLEPROPERTYMANAGER_H
