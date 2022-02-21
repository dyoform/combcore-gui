#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>
#include "construct.h"

class Transaction : public Construct
{
    Q_OBJECT
    Q_PROPERTY(QString destination READ destination CONSTANT)
    Q_PROPERTY(QString source READ source CONSTANT)
    Q_PROPERTY(QStringList signature READ signature CONSTANT)
    Q_PROPERTY(bool active READ active CONSTANT)
public:
    Transaction(QString source, QString destination, QStringList signature, bool active, QString id) {
        _destination = destination;
        _source = source;
        _signature = signature;
        _active = active;
        _id = id;
        _type = TYPE_TRANSACTION;
    }
    QString destination() {return _destination;}
    QString source() {return _source;}
    QStringList signature() { return _signature; }
    bool active() { return _active; }
    QString ID() override {
        return _id;
    }
    QString Active() override {
        return _active ? QString("  ✓") : QString("  ✘");
    }
private:
    QString _destination;
    QString _source;
    QString _id;
    bool _active;
    QStringList _signature;
signals:
};

#endif // TRANSACTION_H
