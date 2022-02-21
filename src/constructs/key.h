#ifndef KEY_H
#define KEY_H
#include <QObject>
#include "construct.h"
class Key : public Construct
{
    Q_OBJECT
    Q_PROPERTY(QString publicKey READ publicKey CONSTANT)
    Q_PROPERTY(int balance READ balance CONSTANT)
    Q_PROPERTY(bool active READ active CONSTANT)
public:
    Key(QString publicKey, int balance, bool active) {
        _publicKey = publicKey;
        _balance = balance;
        _active = active;
        _type = TYPE_KEY;
    }
    QString publicKey() {return _publicKey;}
    int balance() {return _balance;}
    bool active() {return _active;}
    QString ID() override {
        return publicKey();
    }
    QString Active() override {
        return _balance == 0 ? (_active ? QString("  ✓") : QString("")) : QString("  $");
    }
private:
    QString _publicKey;
    int     _balance;
    bool    _active;
};

#endif // KEY_H
