#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include "construct.h"

class Transaction : public Construct
{
    Q_OBJECT
    Q_PROPERTY(QString destination READ destination CONSTANT)
    Q_PROPERTY(QString source READ source CONSTANT)

public:
    Transaction(QString source, QString destination, QString id) {
        _destination = destination;
        _source = source;
        _address = id;
        _type = TYPE_TRANSACTION;
    }
    QString destination() {return _destination;}
    QString source() {return _source;}
    QString ID() override {
        return _address;
    }
private:
    QString _destination;
    QString _source;
    QString _address;
signals:
};

#endif // TRANSACTION_H
