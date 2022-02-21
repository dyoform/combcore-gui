#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QObject>
#include <qqml.h>

#include "datamodel.h"

class SettingsScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString remoteAddress READ remoteAddress WRITE changeRemoteAddress NOTIFY changed)
    Q_PROPERTY(int remotePort READ remotePort WRITE changeRemotePort NOTIFY changed)
    Q_PROPERTY(QStringList output READ output NOTIFY changed)
    QML_ELEMENT
public:
    explicit SettingsScreen(QObject *parent = nullptr);
    void inject(DataModel* model) {
        _model = model;
        QObject::connect(_model, &DataModel::dataChanged, this, [this]{emit changed();});
    }
    QString remoteAddress() {return _model->remoteAddress;}
    int remotePort() {return _model->remotePort;}
    QStringList output() {return _model->output;}
public slots:
    void changeRemoteAddress(QString newAddress) {
        _model->remoteAddress = newAddress;
        emit changed();
    }
    void changeRemotePort(int newPort) {
        _model->remoteAddress = uint16_t(newPort);
        emit changed();
    }
    void save() {
        _model->saveSettings();
    }
private:
    DataModel* _model;
signals:
    void changed();
};

#endif // SETTINGSSCREEN_H
