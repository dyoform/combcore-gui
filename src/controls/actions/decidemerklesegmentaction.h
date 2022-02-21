#ifndef DECIDEMERKLESEGMENTACTION_H
#define DECIDEMERKLESEGMENTACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"

class DecideMerkleSegmentAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY changed)
    Q_PROPERTY(QString signature1 READ signature1 WRITE setSignature1 NOTIFY changed)
    Q_PROPERTY(QString signature2 READ signature2 WRITE setSignature2 NOTIFY changed)
    Q_PROPERTY(QString branchesString READ branchesString WRITE setBranches NOTIFY changed)
    Q_PROPERTY(QString leaf READ leaf WRITE setLeaf NOTIFY changed)

    Q_PROPERTY(QStringList branches READ branches NOTIFY changed)
    Q_PROPERTY(QStringList tips READ tips NOTIFY changed)
    Q_PROPERTY(QString next READ next NOTIFY changed)

    Q_PROPERTY(QString error READ error NOTIFY changed)
    Q_PROPERTY(bool stored READ stored NOTIFY changed)
    Q_PROPERTY(bool got READ got NOTIFY changed)
    QML_ELEMENT
public:
    explicit DecideMerkleSegmentAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }
    QString address() { return _address; }
    QString signature1() { return _signature.length() != 2 ? "" : _signature[0]; }
    QString signature2() { return _signature.length() != 2 ? "" : _signature[1]; }
    QString branchesString() { return _branchesString; }
    QString leaf() { return _leaf; }

    QStringList branches() { return _branches; }
    QStringList tips() { return _tips; }
    QString next() { return _next; }
    QString error() { return _error; }
    bool stored() { return _stored; }
    bool got() {return _got;}
public slots:
    void clear() {
        _branches.clear();
        _tips.clear();
        _next = "";
        _stored = false;
        _got = false;
        emit changed();
    }
    void setAddress(QString address) {
        _address = address;
        clear();
        emit changed();
    }
    void setSignature1(QString sig) {
        if(_signature.length() != 2) {
            _signature.clear();
            _signature.append("");
            _signature.append("");
        }
        _signature[0] = sig;
        clear();
        emit changed();
    }
    void setSignature2(QString sig) {
        if(_signature.length() != 2) {
            _signature.clear();
            _signature.append("");
            _signature.append("");
        }
        _signature[1] = sig;
        clear();
        emit changed();
    }
    void setBranches(QString branches) {
        _branchesString = branches;
        clear();
        emit changed();
    }
    void setLeaf(QString leaf) {
        _leaf = leaf;
        clear();
        emit changed();
    }

    void decideMerkleSegment() {
        //_got = !_got;
        //emit changed();
        //return;

        QJsonObject j;
        j["id"] = "decideMerkleSegment";
        j["method"] = "Control.DecideMerkleSegment";
        QJsonObject k;
        k["address"] = _address;
        k["leaf"] = _leaf;
        QJsonArray signature;
        signature.append(signature1());
        signature.append(signature2());
        k["signature"] = signature;
        QJsonArray branches;
        QStringList b = _branchesString.split(", ");
        for(int i = 0; i < b.length(); i++) {
            branches.append(b[i]);
        }
        k["branches"] = branches;
        QJsonArray a;
        a.append(k);
        j["params"] = a;
        _model->postRequest(j);
    }
    void storeMerkleSegment() {
        QJsonObject j;
        j["id"] = "loadMerkleSegment";
        j["method"] = "Control.LoadMerkleSegment";
        QJsonObject k;
        k["leaf"] = _leaf;
        k["next"] = _next;
        QJsonArray tips;
        tips.append(_tips[0]);
        tips.append(_tips[1]);
        k["tips"] = tips;
        QJsonArray signature;
        signature.append(_signature[0]);
        signature.append(_signature[1]);
        k["signature"] = signature;
        QJsonArray branches;
        for(int i = 0; i < _branches.length(); i++) {
            branches.append(_branches[i]);
        }
        k["branches"] = branches;
        QJsonArray a;
        a.append(k);
        j["params"] = a;


        _model->postRequest(j);
    }
    void gotData(QString id, QJsonObject data) {
        if(id != "decideMerkleSegment" && id != "loadMerkleSegment") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            _error = data["error"].toString();
            emit changed();
            return;
        }

        data = data["result"].toObject();

        if(id == "decideMerkleSegment") {
            _address = data["ID"].toString();
            _leaf = data["Leaf"].toString();
            _next = data["Next"].toString();

            _signature.clear();
            auto a = data["Signature"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _signature.append(a[i].toString());
            }

            _tips.clear();
            a = data["Tips"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _tips.append(a[i].toString());
            }

            _branches.clear();
            a = data["Branches"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _branches.append(a[i].toString());
            }

            _stored = false;
            _got = true;
        }

        if(id == "loadMerkleSegment") {
            _model->getWallet();
            _stored = true;
        }

        emit changed();
    }
private:
    DataModel* _model;
    QString _address;
    QStringList _signature;
    QString _branchesString;
    QString _leaf;

    QStringList _branches;
    QStringList _tips;
    QString _next;

    QString _error;
    bool _stored = false;
    bool _got = false;
signals:
    void changed();
};

#endif // DECIDEMERKLESEGMENTACTION_H
