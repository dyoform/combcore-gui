#ifndef ACTIONCONTROLS_H
#define ACTIONCONTROLS_H

#include <QObject>
#include <qqml.h>

class ActionControls : public QObject {
    Q_OBJECT
    Q_PROPERTY(Action activeAction READ activeAction WRITE changeAction NOTIFY actionChanged)
    Q_ENUMS(Action)
    QML_ELEMENT
public:
    enum Action {
        ACTION_OVERVIEW,
        ACTION_WALLET,
        ACTION_ACTIONS,
        ACTION_SETTINGS
    };
    explicit ActionControls(QObject *parent = nullptr);
    Action activeAction() {return _activeAction; };
private:
    Action _activeAction = ACTION_OVERVIEW;
public slots:
    void changeAction(Action action);
signals:
    void actionChanged();
};

#endif // ACTIONCONTROLS_H
