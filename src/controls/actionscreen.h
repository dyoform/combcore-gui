#ifndef ACTIONSCREEN_H
#define ACTIONSCREEN_H

#include <QObject>
#include "datamodel.h"
#include "generatekeyaction.h"
#include "createstackaction.h"
class ActionScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int activeAction READ activeAction WRITE changeAction NOTIFY actionChanged)
    Q_PROPERTY(GenerateKeyAction* generateKeyAction READ generateKeyAction CONSTANT)
    Q_PROPERTY(CreateStackAction* createStackAction READ createStackAction CONSTANT)
    QML_ELEMENT
public:
    explicit ActionScreen(QObject *parent = nullptr);
    void inject(DataModel* model) {
        _model = model;
        _generateKeyAction.inject(model);
        _createStackAction.inject(model);
    }
    int activeAction() { return _index; }
    GenerateKeyAction* generateKeyAction() { return &_generateKeyAction; }
    CreateStackAction* createStackAction() { return &_createStackAction; }
public slots:
    void changeAction(int index) {
        if(index == _index)
            return;
        _index = index;
        emit actionChanged();
    }
private:
    DataModel* _model;
    int _index;
    GenerateKeyAction _generateKeyAction;
    CreateStackAction _createStackAction;

signals:
    void actionChanged();
};

#endif // ACTIONSCREEN_H
