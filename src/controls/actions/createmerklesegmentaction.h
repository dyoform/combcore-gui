#ifndef CREATEMERKLESEGMENTACTION_H
#define CREATEMERKLESEGMENTACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"

class CreateMerkleSegmentAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address NOTIFY changed)
    Q_PROPERTY(QString tip1 READ tip1 WRITE setTip1 NOTIFY changed)
    Q_PROPERTY(QString tip2 READ tip2 WRITE setTip2 NOTIFY changed)
    Q_PROPERTY(QString next READ next WRITE setNext NOTIFY changed)
    Q_PROPERTY(QString root READ root WRITE setRoot NOTIFY changed)
    Q_PROPERTY(QString error READ error NOTIFY changed)
    Q_PROPERTY(bool stored READ stored NOTIFY changed)
    QML_ELEMENT
public:
    explicit CreateMerkleSegmentAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }
    QString address() { return _address; }
    QString tip1() { return _tip1; }
    QString tip2() { return _tip2; }
    QString next() { return _next; }
    QString root() { return _root; }
    QString error() { return _error; }
    bool stored() { return _stored; }
public slots:
    void setTip1(QString tip1) {
        _tip1 = tip1;
        _address = "";
        emit changed();
    }
    void setTip2(QString tip2) {
        _tip2 = tip2;
        _address = "";
        emit changed();
    }
    void setNext(QString next) {
        _next = next;
        _address = "";
        emit changed();
    }
    void setRoot(QString root) {
        _root = root;
        _address = "";
        emit changed();
    }
    void createUnsignedMerkleSegment() {
        _error = "";
        QJsonObject j;
        j["id"] = "constructUnsignedMerkleSegment";
        j["method"] = "Control.ConstructUnsignedMerkleSegment";
        QJsonObject k;
        QJsonArray tips;
        tips.append(_tip1);
        tips.append(_tip2);
        k["tips"] = tips;
        k["next"] = _next;
        k["root"] = _root;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void loadUnsignedMerkleSegment() {
        _error = "";
        QJsonObject j;
        j["id"] = "loadUnsignedMerkleSegment";
        j["method"] = "Control.LoadUnsignedMerkleSegment";
        QJsonObject k;
        QJsonArray tips;
        tips.append(_tip1);
        tips.append(_tip2);
        k["tips"] = tips;
        k["next"] = _next;
        k["root"] = _root;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void gotData(QString id, QJsonObject data) {
        if(id != "constructUnsignedMerkleSegment" && id != "loadUnsignedMerkleSegment") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            _error = data["error"].toString();
            emit changed();
            return;
        }
        data = data["result"].toObject();

        if(id == "constructUnsignedMerkleSegment") {
            _root = data["Root"].toString();
            _next = data["Next"].toString();
            QJsonArray tips = data["Tips"].toArray();
            _tip1 = tips[0].toString();
            _tip2 = tips[1].toString();
            _address = data["ID"].toString();

            _stored = _model->haveConstruct(_address);
        }

        if(id == "loadUnsignedMerkleSegment") {
            _model->getWallet();
            _stored = true;
        }

        emit changed();
    }
private:
    DataModel* _model;
    QString _tip1;
    QString _tip2;
    QString _next;
    QString _root;
    QString _address;
    QString _error;
    bool _stored = false;
signals:
    void changed();
};

#endif // CREATEMERKLESEGMENTACTION_H
