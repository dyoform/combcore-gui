#ifndef ACTIONSCREEN_H
#define ACTIONSCREEN_H

#include <QObject>
#include "datamodel.h"
#include "generatekeyaction.h"
#include "createstackaction.h"
#include "createtransactionaction.h"
#include "commandaction.h"
class ActionScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int activeAction READ activeAction WRITE changeAction NOTIFY actionChanged)
    Q_PROPERTY(GenerateKeyAction* generateKeyAction READ generateKeyAction CONSTANT)
    Q_PROPERTY(CreateStackAction* createStackAction READ createStackAction CONSTANT)
    Q_PROPERTY(CreateTransactionAction* createTransactionAction READ createTransactionAction CONSTANT)

    Q_PROPERTY(CommandAction* commandAction READ commandAction CONSTANT)
    QML_ELEMENT
public:
    explicit ActionScreen(QObject *parent = nullptr);
    void inject(DataModel* model) {
        _model = model;
        _generateKeyAction.inject(model);
        _createStackAction.inject(model);
        _createTransactionAction.inject(model);
        _commandAction.inject(model);
    }
    int activeAction() { return _index; }
    GenerateKeyAction* generateKeyAction() { return &_generateKeyAction; }
    CreateStackAction* createStackAction() { return &_createStackAction; }
    CreateTransactionAction* createTransactionAction() { return &_createTransactionAction; }
    CommandAction* commandAction() { return &_commandAction; }
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
    CreateTransactionAction _createTransactionAction;
    CommandAction _commandAction;
signals:
    void actionChanged();
};

#endif // ACTIONSCREEN_H
