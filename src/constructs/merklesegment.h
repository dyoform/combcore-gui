#ifndef MERKLESEGMENT_H
#define MERKLESEGMENT_H

#include <QObject>
#include "construct.h"

class MerkleSegment : public Construct
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address CONSTANT)
    Q_PROPERTY(QString root READ root CONSTANT)
    Q_PROPERTY(QString next READ next CONSTANT)
    Q_PROPERTY(QStringList tips READ tips CONSTANT)
    Q_PROPERTY(int balance READ balance CONSTANT)

    Q_PROPERTY(QString leaf READ leaf CONSTANT)
    Q_PROPERTY(QStringList signature READ signature CONSTANT)
    Q_PROPERTY(QStringList branches READ branches CONSTANT)

    Q_PROPERTY(bool active READ active CONSTANT)
public:
    MerkleSegment(QString address, QString root, QString next, QStringList tips, QString leaf, QStringList signature, QStringList branches, int balance, bool active) {
        _address = address;
        _balance = balance;
        _root = root;
        _next = next;
        _tips = tips;
        _leaf = leaf;
        _signature = signature;
        _branches = branches;
        _active = active;
        _type = TYPE_MERKLE_SEGMENT;
    }
    QString address() {
        return _address;
    }
    int balance() {
        return _balance;
    }
    QString root() {
        return _root;
    }
    QString next() {
        return _next;
    }
    QStringList tips() {
        return _tips;
    }
    QString leaf() {
        return _leaf;
    }
    QStringList signature() {
        return _signature;
    }
    QStringList branches() {
        return _branches;
    }
    bool active() {
        return _active;
    }
    QString ID() override {
        return _address;
    }
    QString Active() override {
        return _leaf == "" ? "" : (_active ? QString("  ✓") : QString("  ✘"));
    }
private:
    QString _address;
    int     _balance;
    QString _root;
    QString _next;
    QStringList _tips;
    QString _leaf;
    QStringList _signature;
    QStringList _branches;
    bool _active;
signals:
};

#endif // MERKLESEGMENT_H
