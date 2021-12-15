#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <QObject>
#include <qqml.h>

enum ConstructType {
    TYPE_NONE,
    TYPE_KEY,
    TYPE_STACK,
    TYPE_TRANSACTION
};
const QString ConstructTypeNames[] = {"None", "Key", "Stack", "Transaction"};

class Construct : public QObject
{
    Q_OBJECT
    Q_ENUM(ConstructType)
    QML_ELEMENT
public:
    explicit Construct() {}
    ConstructType type() {return _type;}
    QString typeName() {return ConstructTypeNames[_type];}
    virtual QString ID() {return "";}
protected:
    ConstructType _type = TYPE_NONE;

signals:

};

#endif // CONSTRUCT_H
