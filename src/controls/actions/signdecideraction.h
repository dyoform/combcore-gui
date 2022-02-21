#ifndef SIGNDECIDERACTION_H
#define SIGNDECIDERACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"

class SignDeciderAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setID NOTIFY changed)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY changed)
    Q_PROPERTY(QStringList signature READ signature NOTIFY changed)
    Q_PROPERTY(QString error READ error NOTIFY changed)
    Q_PROPERTY(bool stored READ stored NOTIFY changed)
    QML_ELEMENT
public:
    explicit SignDeciderAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }
    QString id() { return _id; }
    QString destination() { return QString("%1").arg(_destination); }
    QStringList signature() { return _signature; }
    QString error() { return _error; }
    bool stored() { return _stored; }
public slots:
    void setID(QString id) {
        _id = id;
        _signature.clear();
        emit changed();
    }
    void setDestination(QString sum) {
        _destination = sum.toULongLong();
        _signature.clear();
        emit changed();
    }
    void signDecider() {
        QJsonObject j;
        j["id"] = "signDecider";
        j["method"] = "Control.SignDecider";
        QJsonObject k;
        k["destination"] = _destination;
        k["id"] = _id;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void storeSignature() {
        _model->checkSignature(_signature);
        _stored = true;
        emit changed();
    }
    void gotData(QString id, QJsonObject data) {
        if(id != "signDecider") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            _error = data["error"].toString();
            emit changed();
            return;
        }

        if(id == "signDecider") {
            auto a = data["result"].toArray();
            _signature.clear();
            for(int i = 0; i < a.size(); i++) {
                _signature.append(a[i].toString());
            }
            _stored = false;
        }

        emit changed();
    }
private:
    DataModel* _model;
    QString _id;
    int _destination = false;
    QStringList _signature;
    QString _error;
    bool _stored = false;
signals:
    void changed();
};

#endif // SIGNDECIDERACTION_H
