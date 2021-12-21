#ifndef COMMANDACTION_H
#define COMMANDACTION_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "datamodel.h"

class CommandAction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString method READ method WRITE setMethod NOTIFY changed)
    Q_PROPERTY(QString params READ params WRITE setParams NOTIFY changed)
    Q_PROPERTY(QString result READ result NOTIFY changed)
    Q_PROPERTY(QString error READ error NOTIFY changed)
    QML_ELEMENT
public:
    explicit CommandAction(QObject *parent = nullptr): QObject{parent} { }
    void inject(DataModel* model) {
        _model = model;
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
    }
    QString method() { return _method; }
    QString params() { return _params; }
    QString result() { return _result; }
    QString error() { return _error; }
public slots:
    void setMethod(QString method) {
        _method = method;
        emit changed();
    }
    void setParams(QString params) {
        _params = params;
        emit changed();
    }
    void sendCommand() {
        _error = "";
        QJsonObject j;
        j["id"] = "customCommand";
        j["method"] = "Control." + _method;
        QJsonParseError e;
        QJsonDocument d = QJsonDocument().fromJson(_params.toUtf8(), &e);
        if(e.error != QJsonParseError::NoError) {
            _error = e.errorString();
            emit changed();
            return;
        }
        if(!d.isArray()) {
            _error = "parameters must be a JSON array";
            emit changed();
            return;
        }
        j["params"] = d.array();
        _model->postRequest(j);
    }
    void gotData(QString id, QJsonObject data) {
        if(id != "customCommand") {
            return;
        }
        QJsonDocument d(data);
        _result = d.toJson(QJsonDocument::Indented);
        emit changed();
    }
private:
    DataModel* _model;
    QString _method;
    QString _params;
    QString _result;
    QString _error;
signals:
    void changed();
};

#endif // COMMANDACTION_H
