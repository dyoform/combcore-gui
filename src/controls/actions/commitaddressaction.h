#ifndef COMMITADDRESSACTION_H
#define COMMITADDRESSACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"

class CommitAddressAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY changed)
    Q_PROPERTY(QString commit READ commit NOTIFY changed)
    Q_PROPERTY(QString error READ error NOTIFY changed)
    Q_PROPERTY(bool stored READ stored NOTIFY changed)
    QML_ELEMENT
public:
    explicit CommitAddressAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }
    QString address() { return _address; }
    QString commit() { return _commit; }
    QString error() { return _error; }
    bool stored() { return _stored; }
public slots:
    void setAddress(QString address) {
        _address = address;
        _commit = "";
        emit changed();
    }
    void commitAddress() {
        QJsonObject j;
        j["id"] = "commitAddress";
        j["method"] = "Control.CommitAddress";
        auto a = QJsonArray();
        a.append(_address);
        j["params"] = a;
        _model->postRequest(j);
    }
    void storeCommit() {
        _model->checkClaim(_address);
    }
    void gotData(QString id, QJsonObject data) {
        if(id != "commitAddress") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            _error = data["error"].toString();
            emit changed();
            return;
        }
        _commit = data["result"].toString();
        emit changed();
    }
private:
    DataModel* _model;
    QString _address;
    QString _commit;
    QString _error;
    bool _stored = false;
signals:
    void changed();
};

#endif // CREATESTACKACTION_H
