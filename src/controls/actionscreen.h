#ifndef ACTIONSCREEN_H
#define ACTIONSCREEN_H

#include <QObject>
#include "datamodel.h"
#include "generatekeyaction.h"
#include "createstackaction.h"
#include "createtransactionaction.h"
#include "generatedecideraction.h"
#include "createmerklesegmentaction.h"
#include "signdecideraction.h"
#include "decidemerklesegmentaction.h"
#include "commitaddressaction.h"
#include "commandaction.h"
class ActionScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int activeAction READ activeAction WRITE changeAction NOTIFY actionChanged)
    Q_PROPERTY(GenerateKeyAction* generateKeyAction READ generateKeyAction CONSTANT)
    Q_PROPERTY(GenerateDeciderAction* generateDeciderAction READ generateDeciderAction CONSTANT)
    Q_PROPERTY(CreateStackAction* createStackAction READ createStackAction CONSTANT)
    Q_PROPERTY(CreateTransactionAction* createTransactionAction READ createTransactionAction CONSTANT)
    Q_PROPERTY(CreateMerkleSegmentAction* createMerkleSegmentAction READ createMerkleSegmentAction CONSTANT)
    Q_PROPERTY(SignDeciderAction* signDeciderAction READ signDeciderAction CONSTANT)
    Q_PROPERTY(DecideMerkleSegmentAction* decideMerkleSegmentAction READ decideMerkleSegmentAction CONSTANT)
    Q_PROPERTY(CommitAddressAction* commitAddressAction READ commitAddressAction CONSTANT)
    Q_PROPERTY(CommandAction* commandAction READ commandAction CONSTANT)
    QML_ELEMENT
public:
    explicit ActionScreen(QObject *parent = nullptr);
    void inject(DataModel* model) {
        _model = model;
        _generateKeyAction.inject(model);
        _generateDeciderAction.inject(model);
        _createStackAction.inject(model);
        _createTransactionAction.inject(model);
        _createMerkleSegmentAction.inject(model);
        _signDeciderAction.inject(model);
        _decideMerkleSegmentAction.inject(model);
        _commitAddressAction.inject(model);
        _commandAction.inject(model);
    }
    int activeAction() { return _index; }
    GenerateKeyAction* generateKeyAction() { return &_generateKeyAction; }
    GenerateDeciderAction* generateDeciderAction() { return &_generateDeciderAction; }
    CreateStackAction* createStackAction() { return &_createStackAction; }
    CreateTransactionAction* createTransactionAction() { return &_createTransactionAction; }
    CreateMerkleSegmentAction* createMerkleSegmentAction() { return &_createMerkleSegmentAction; }
    DecideMerkleSegmentAction* decideMerkleSegmentAction() { return &_decideMerkleSegmentAction; }
    SignDeciderAction* signDeciderAction() { return &_signDeciderAction; }
    CommitAddressAction* commitAddressAction() { return &_commitAddressAction; }
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
    GenerateDeciderAction _generateDeciderAction;
    CreateStackAction _createStackAction;
    CreateTransactionAction _createTransactionAction;
    CreateMerkleSegmentAction _createMerkleSegmentAction;
    DecideMerkleSegmentAction _decideMerkleSegmentAction;
    SignDeciderAction _signDeciderAction;
    CommitAddressAction _commitAddressAction;
    CommandAction _commandAction;
signals:
    void actionChanged();
};

#endif // ACTIONSCREEN_H
