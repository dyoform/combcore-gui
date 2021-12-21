#ifndef GUIMODEL_H
#define GUIMODEL_H

#include <QObject>
#include <QPoint>
#include <qqml.h>
#include "screencontrols.h"
#include "actionscreen.h"
#include "overviewscreen.h"
#include "walletscreen.h"
#include "settingsscreen.h"
#include "datamodel.h"

class GUIModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(ScreenControls* screenControls READ screenControls CONSTANT)
    Q_PROPERTY(OverviewScreen* overview READ overview CONSTANT)
    Q_PROPERTY(ActionScreen* action READ action CONSTANT)
    Q_PROPERTY(WalletScreen* wallet READ wallet CONSTANT)
    Q_PROPERTY(SettingsScreen* settings READ settings CONSTANT)
    QML_ELEMENT
public:
    explicit GUIModel(DataModel* model) {
        _model = model;
        _overviewScreen.inject(model);
        _actionScreen.inject(model);
        _walletScreen.inject(model);
        _settingsScreen.inject(model);
    }
    ScreenControls* screenControls() {return &_screenControls;}
    OverviewScreen* overview() {return &_overviewScreen;}
    ActionScreen* action() {return &_actionScreen;}
    WalletScreen* wallet() {return &_walletScreen;}
    SettingsScreen* settings() {return &_settingsScreen;}
private:
    DataModel* _model;
    ScreenControls _screenControls;
    OverviewScreen _overviewScreen;
    ActionScreen _actionScreen;
    WalletScreen _walletScreen;
    SettingsScreen _settingsScreen;
signals:
};

#endif // GUIMODEL_H
