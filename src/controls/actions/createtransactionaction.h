#ifndef CREATETRANSACTIONACTION_H
#define CREATETRANSACTIONACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"


class CreateTransactionAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY changed)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY changed)
    Q_PROPERTY(QString id READ id NOTIFY changed)
    Q_PROPERTY(QStringList signature READ signature NOTIFY changed)
    Q_PROPERTY(QString error READ error NOTIFY changed)
    Q_PROPERTY(bool stored READ stored NOTIFY changed)
    QML_ELEMENT
public:
    explicit CreateTransactionAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }

    QString source() { return _source; }
    QString destination() { return _destination; }
    QString id() { return _id; }
    QStringList signature() { return _signature; }
    QString error() { return _error; }
    bool stored() { return _stored; }
public slots:
    void setSource(QString source) {
        _source = source;
        _id = "";
        _error = "";
        _signature.clear();
        emit changed();
    }
    void setDestination(QString destination) {
        _destination = destination;
        _id = "";
        _error = "";
        _signature.clear();
        emit changed();
    }
    void createTransaction() {
        _error = "";
        QJsonObject j;
        j["id"] = "constructTransaction";
        j["method"] = "Control.ConstructTransaction";
        QJsonObject k;
        k["source"] = _source;
        k["destination"] = _destination;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void loadTransaction() {
        _error = "";
        QJsonObject j;
        j["id"] = "loadTransaction";
        j["method"] = "Control.LoadTransaction";
        QJsonObject k;
        k["source"] = _source;
        k["destination"] = _destination;
        QJsonArray s;
        for(int i = 0; i < _signature.size(); i++) {
            s.append(_signature[i]);
        }
        k["signature"] = s;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void gotData(QString id, QJsonObject data) {
        if(id != "constructTransaction" && id != "loadTransaction") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            _error = data["error"].toString();
            emit changed();
            return;
        }
        data = data["result"].toObject();

        if(id == "constructTransaction") {
            _source = data["Source"].toString();
            _destination = data["Destination"].toString();
            _id = data["ID"].toString();

            _signature.clear();
            auto a = data["Signature"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _signature.append(a[i].toString());
            }

            _stored = _model->haveConstruct(_id);
        }

        if(id == "loadTransaction") {
            _model->syncWallet();
            _stored = true;
        }

        emit changed();
    }
private:
    DataModel* _model;
    QString _source;
    QString _destination;
    QStringList _signature;
    QString _id;
    QString _error;
    bool _stored;
signals:
    void changed();
};

#endif // CREATETRANSACTIONACTION_H
