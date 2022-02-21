#ifndef DECIDER_H
#define DECIDER_H
#include <QObject>
#include "construct.h"
class Decider : public Construct
{
    Q_OBJECT
    Q_PROPERTY(QString id READ ID CONSTANT)
    Q_PROPERTY(QStringList tips READ tips CONSTANT)

public:
    Decider(QString id, QStringList tips) {
        _id = id;
        _tips = tips;
        _type = TYPE_DECIDER;
    }
    QString ID() override {
        return _id;
    }
    QStringList tips() {
        return _tips;
    }
private:
    QString _id;
    QStringList _tips;
};

#endif // DECIDER_H
