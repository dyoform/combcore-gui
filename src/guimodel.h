#ifndef GUIMODEL_H
#define GUIMODEL_H

#include <QObject>
#include <QPoint>
#include <qqml.h>
#include "actioncontrols.h"
#include "pendingtable.h"
#include "wallettable.h"
#include "datamodel.h"

class GUIModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(ActionControls* actionControls READ actionControls NOTIFY actionControlsChanged)
    Q_PROPERTY(PendingTable* pendingTable READ pendingTable NOTIFY pendingTableChanged)
    Q_PROPERTY(WalletTable* walletTable READ walletTable NOTIFY walletTableChanged)
    QML_ELEMENT
public:
    explicit GUIModel(DataModel* model);
    ActionControls* actionControls() {return &_actionControls;}
    PendingTable* pendingTable() {return &_pendingTable;}
    WalletTable* walletTable() {return &_walletTable;}
private:
    DataModel* _model;
    ActionControls _actionControls;
    PendingTable _pendingTable;
    WalletTable _walletTable;
signals:
    void actionControlsChanged();
    void pendingTableChanged();
    void walletTableChanged();
};

#endif // GUIMODEL_H
