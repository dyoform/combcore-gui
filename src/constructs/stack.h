#ifndef STACK_H
#define STACK_H
#include <QObject>
#include "construct.h"
class Stack : public Construct
{
    Q_OBJECT
    Q_PROPERTY(QString destination READ destination CONSTANT)
    Q_PROPERTY(QString change READ change CONSTANT)
    Q_PROPERTY(int sum READ sum CONSTANT)

public:
    Stack(QString destination, QString change, int sum, QString address) {
        _destination = destination;
        _change = change;
        _sum = sum;
        _address = address;
        _type = TYPE_STACK;
    }
    QString destination() {return _destination;}
    QString change() {return _change;}
    int sum() {return _sum;}
    QString ID() override {
        return _address;
    }
private:
    QString _destination;
    QString _change;
    QString _address;
    int     _sum;
signals:
};

#endif // STACK_H
