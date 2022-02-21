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
    Q_PROPERTY(int balance READ balance CONSTANT)
    Q_PROPERTY(bool active READ active CONSTANT)
public:
    Stack(QString destination, QString change, int sum, QString address, int balance, bool active) {
        _destination = destination;
        _change = change;
        _sum = sum;
        _address = address;
        _active = active;
        _balance = balance;
        _type = TYPE_STACK;
    }
    QString destination() {return _destination;}
    QString change() {return _change;}
    int sum() {return _sum;}
    int balance() {return _balance;}
    bool active() {return _active;}
    QString ID() override {
        return _address;
    }
    QString Active() override {
        return _balance == 0 ? (_active ? QString("  ✓") : QString("")) : QString("  $");
    }
private:
    QString _destination;
    QString _change;
    QString _address;
    bool _active;
    int     _sum;
    int _balance;
signals:
};

#endif // STACK_H
