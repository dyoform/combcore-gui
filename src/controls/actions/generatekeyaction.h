#ifndef GENERATEKEYACTION_H
#define GENERATEKEYACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"

class GenerateKeyAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString publicKey READ publicKey NOTIFY changed)
    Q_PROPERTY(QStringList privateKey READ privateKey NOTIFY changed)
    Q_PROPERTY(QString error READ error NOTIFY changed)
    Q_PROPERTY(bool stored READ stored NOTIFY changed)
    QML_ELEMENT
public:
    explicit GenerateKeyAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }
    QString publicKey() { return _publicKey; }
    QStringList privateKey() { return _privateKey; }
    QString error() { return _error; }
    bool stored() { return _stored; }
public slots:
    void generateNew() {
        QJsonObject j;
        j["id"] = "generateKey";
        j["method"] = "Control.GenerateKey";
        j["params"] = QJsonArray();
        _model->postRequest(j);
    }
    void saveKey() {
        QJsonObject j;
        j["id"] = "loadKey";
        j["method"] = "Control.LoadKey";
        QJsonObject k;
        k["public"] = _publicKey;
        QJsonArray p;
        for(int i = 0; i < _privateKey.size(); i++) {
            p.append(_privateKey[i]);
        }
        k["private"] = p;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void gotData(QString id, QJsonObject data) {
        if(id != "generateKey" && id != "loadKey") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            _error = data["error"].toString();
            emit changed();
            return;
        }
        data = data["result"].toObject();

        if(id == "generateKey") {
            _publicKey = data["Public"].toString();
            _privateKey.clear();
            auto a = data["Private"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _privateKey.append(a[i].toString());
            }

            _stored = _model->haveConstruct(_publicKey);
        }

        if(id == "loadKey") {
            _stored = true;
            _model->syncWallet();
        }

        emit changed();
    }
private:
    DataModel* _model;
    QString _publicKey;
    QStringList _privateKey;
    QString _error;
    bool _stored;
signals:
    void changed();
};

#endif // GENERATEKEYACTION_H
