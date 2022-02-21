#ifndef CREATESTACKACTION_H
#define CREATESTACKACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"

class CreateStackAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address NOTIFY changed)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY changed)
    Q_PROPERTY(QString change READ change WRITE setChange NOTIFY changed)
    Q_PROPERTY(QString sum READ sum WRITE setSum NOTIFY changed)
    Q_PROPERTY(QString error READ error NOTIFY changed)
    Q_PROPERTY(bool stored READ stored NOTIFY changed)
    QML_ELEMENT
public:
    explicit CreateStackAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }
    QString address() { return _address; }
    QString destination() { return _destination; }
    QString change() { return _change; }
    QString sum() { return QString("%1").arg(_sum); }
    QString error() { return _error; }
    bool stored() { return _stored; }
public slots:
    void setDestination(QString destination) {
        _destination = destination;
        _address = "";
        emit changed();
    }
    void setChange(QString change) {
        _change = change;
        _address = "";
        emit changed();
    }
    void setSum(QString sum) {
        _sum = sum.toULongLong();
        _address = "";
        emit changed();
    }
    void createStack() {
        _error = "";
        QJsonObject j;
        j["id"] = "constructStack";
        j["method"] = "Control.ConstructStack";
        QJsonObject k;
        k["destination"] = _destination;
        k["change"] = _change;
        k["sum"] = (int)_sum;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void loadStack() {
        _error = "";
        QJsonObject j;
        j["id"] = "loadStack";
        j["method"] = "Control.LoadStack";
        QJsonObject k;
        k["destination"] = _destination;
        k["change"] = _change;
        k["sum"] = (int)_sum;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void gotData(QString id, QJsonObject data) {
        if(id != "constructStack" && id != "loadStack") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            _error = data["error"].toString();
            emit changed();
            return;
        }
        data = data["result"].toObject();

        if(id == "constructStack") {
            _destination = data["Destination"].toString();
            _change = data["Change"].toString();
            _sum = data["Sum"].toInt();
            _address = data["Address"].toString();

            _stored = _model->haveConstruct(_address);
        }

        if(id == "loadStack") {
            _model->getWallet();
            _stored = true;
        }

        emit changed();
    }
private:
    DataModel* _model;
    QString _destination;
    QString _change;
    uint64_t _sum = 0;
    QString _address;
    QString _error;
    bool _stored = false;
signals:
    void changed();
};

#endif // CREATESTACKACTION_H
