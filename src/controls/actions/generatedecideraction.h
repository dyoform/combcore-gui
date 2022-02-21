#ifndef GENERATEDECIDERACTION_H
#define GENERATEDECIDERACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"

class GenerateDeciderAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY changed)
    Q_PROPERTY(QStringList privateKey READ privateKey NOTIFY changed)
    Q_PROPERTY(QStringList tips READ tips NOTIFY changed)
    Q_PROPERTY(QString error READ error NOTIFY changed)
    Q_PROPERTY(bool stored READ stored NOTIFY changed)
    QML_ELEMENT
public:
    explicit GenerateDeciderAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }
    QString id() { return _id; }
    QStringList privateKey() { return _privateKey; }
    QStringList tips() { return _tips; }
    QString error() { return _error; }
    bool stored() { return _stored; }
public slots:
    void generateNew() {
        QJsonObject j;
        j["id"] = "generateDecider";
        j["method"] = "Control.GenerateDecider";
        j["params"] = QJsonArray();
        _model->postRequest(j);
    }
    void saveDecider() {
        QJsonObject j;
        j["id"] = "loadDecider";
        j["method"] = "Control.LoadDecider";
        QJsonObject k;
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
        if(id != "generateDecider" && id != "loadDecider") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            _error = data["error"].toString();
            emit changed();
            return;
        }
        data = data["result"].toObject();

        if(id == "generateDecider") {
            _id = data["ID"].toString();
            _privateKey.clear();
            auto a = data["Private"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _privateKey.append(a[i].toString());
            }

            _tips.clear();
            a = data["Tips"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _tips.append(a[i].toString());
            }

            _stored = _model->haveConstruct(_id);
        }

        if(id == "loadDecider") {
            _stored = true;
            _model->getWallet();
        }

        emit changed();
    }
private:
    DataModel* _model;
    QString _id;
    QStringList _privateKey;
    QStringList _tips;
    QString _error;
    bool _stored = false;
signals:
    void changed();
};

#endif // GENERATEDECIDERACTION_H
