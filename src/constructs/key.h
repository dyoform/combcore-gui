#ifndef KEY_H
#define KEY_H
#include <QObject>
#include "construct.h"
class Key : public Construct
{
    Q_OBJECT
    Q_PROPERTY(QString publicKey READ publicKey CONSTANT)
    Q_PROPERTY(int balance READ balance NOTIFY balanceChanged)

public:
    Key(QString publicKey, int balance) {
        _publicKey = publicKey;
        _balance = balance;
        _type = TYPE_KEY;
    }
    QString publicKey() {return _publicKey;}
    int balance() {return _balance;}
    void setBalance(int nats) {
        _balance = nats;
        emit balanceChanged();
    }
    QString ID() override {
        return publicKey();
    }
private:
    QString _publicKey;
    int     _balance;
signals:
    void balanceChanged();
};

#endif // KEY_H
