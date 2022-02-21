#ifndef WALLETSCREEN_H
#define WALLETSCREEN_H

#include <QObject>
#include <qqml.h>

#include "datamodel.h"
#include "wallettable.h"
class WalletScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WalletTable* walletTable READ walletTable CONSTANT)
    QML_ELEMENT
public:
    explicit WalletScreen(QObject *parent = nullptr);
    void inject(DataModel* model) {
        _model = model;
        _walletTable.inject(model);
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
        connect(_model, SIGNAL(connectedChanged(bool)), this, SLOT(connectedChanged(bool)));
    }
    WalletTable* walletTable() {return &_walletTable;}
    void processKey(QJsonObject key) {
        QString publicKey = key["Public"].toString();
        int balance = key["Balance"].toInt();
        bool active = key["Active"].toBool(false);
        _model->addConstruct(new Key(publicKey, balance, active));
    }
    void processStack(QJsonObject stack) {
        QString destination = stack["Destination"].toString();
        QString change = stack["Change"].toString();
        QString address = stack["Address"].toString();
        bool active = stack["Active"].toBool(false);
        int sum = stack["Sum"].toInt();
        int balance = stack["Balance"].toInt();
        _model->addConstruct(new Stack(destination, change, sum, address, balance, active));
    }
    void processTransaction(QJsonObject tx) {
        QString source = tx["Source"].toString();
        QString destination = tx["Destination"].toString();
        QString id = tx["ID"].toString();
        bool active = tx["Active"].toBool(false);
        QStringList signature;
        auto a = tx["Signature"].toArray();
        for(int i = 0; i < a.size(); i++) {
            signature.append(a[i].toString());
        }
        _model->addConstruct(new Transaction(source, destination, signature, active, id));
        _model->checkSignature(signature);
    }
    void processDecider(QJsonObject decider) {
        QString id = decider["ID"].toString();
        QStringList tips;

        auto a = decider["Tips"].toArray();
        for(int i = 0; i < a.size(); i++) {
            tips.append(a[i].toString());
        }
        _model->addConstruct(new Decider(id, tips));
    }
    void processMerkleSegment(QJsonObject m) {
        QString address = m["ID"].toString();
        QString tip1 = m["Tips"].toArray()[0].toString();
        QString tip2 = m["Tips"].toArray()[1].toString();
        QString next = m["Next"].toString();
        QString root = m["Root"].toString();

        QString leaf = m["Leaf"].toString();
        bool active = m["Active"].toBool();


        QStringList tips;
        auto a = m["Tips"].toArray();
        for(int i = 0; i < a.size(); i++) {
            tips.append(a[i].toString());
        }

        QStringList signature;
        a = m["Signature"].toArray();
        for(int i = 0; i < a.size(); i++) {
            signature.append(a[i].toString());
        }

        QStringList branches;
        a = m["Branches"].toArray();
        for(int i = 0; i < a.size(); i++) {
            branches.append(a[i].toString());
        }
        int balance = m["Balance"].toInt();

        _model->addConstruct(new MerkleSegment(address, root, next, tips, leaf, signature, branches, balance, active));
        _model->checkSignature(signature);
    }

    void processConstructs(QJsonObject wallet) {
        _model->constructs.clear();
        if(wallet["Keys"].isArray()) {
            QJsonArray keys = wallet["Keys"].toArray();
            for(int i = 0; i < keys.size(); i++)
                processKey(keys[i].toObject());
        }
        if(wallet["Stacks"].isArray()) {
            QJsonArray stacks = wallet["Stacks"].toArray();
            for(int i = 0; i < stacks.size(); i++)
                processStack(stacks[i].toObject());
        }
        if(wallet["TXs"].isArray()) {
            QJsonArray txs = wallet["TXs"].toArray();
            for(int i = 0; i < txs.size(); i++)
                processTransaction(txs[i].toObject());
        }
        if(wallet["Deciders"].isArray()) {
            QJsonArray deciders = wallet["Deciders"].toArray();
            for(int i = 0; i < deciders.size(); i++)
                processDecider(deciders[i].toObject());
        }
        if(wallet["Merkles"].isArray()) {
            QJsonArray merkles = wallet["Merkles"].toArray();
            for(int i = 0; i < merkles.size(); i++)
                processMerkleSegment(merkles[i].toObject());
        }
        if(wallet["UnsignedMerkles"].isArray()) {
            QJsonArray merkles = wallet["UnsignedMerkles"].toArray();
            for(int i = 0; i < merkles.size(); i++)
                processMerkleSegment(merkles[i].toObject());
        }
        _model->update();
    }
public slots:
    void gotData(QString id, QJsonObject data) {
        if(id != "getWallet" && id != "loadWallet" && id != "saveWallet") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            qInfo() << data["error"].toString();
            return;
        }

        if(id == "getWallet") {
            data = data["result"].toObject();
            processConstructs(data);
        }

        if(id == "loadWallet") {
            getWallet();
        }

        if(id == "saveWallet") {
            actuallySaveWallet(_savePath, data["result"].toString());
        }
    }
    void connectedChanged(bool connected) {
        if(connected) {
            getWallet();
        } else {
            _model->constructs.clear();
            _model->pending_commits.clear();
            _model->update();
        }
    }
    void loadWallet(QUrl path) {
        QFile file(path.toLocalFile());
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
        QString data = file.readAll();
        file.close();

        QJsonObject j;
        j["id"] = "loadWallet";
        j["method"] = "Control.LoadWallet";
        QJsonArray p;
        p.append(QJsonValue(data));
        j["params"] = p;
        _model->postRequest(j);
    }
    void saveWallet(QUrl path) {
        _savePath = path.toLocalFile();

        QJsonObject j;
        j["id"] = "saveWallet";
        j["method"] = "Control.SaveWallet";
        j["params"] = QJsonArray();
        _model->postRequest(j);
    }
    void getWallet() {
        QJsonObject j;
        j["id"] = "getWallet";
        j["method"] = "Control.GetWallet";
        j["params"] = QJsonArray();
        _model->postRequest(j);
    }
private:
    void actuallySaveWallet(QString path, QString data) {
        QFile file(path);
            if (!file.open(QIODevice::NewOnly | QIODevice::Text))
                return;
        file.write(data.toUtf8());
        file.close();
    }
    QString _savePath = "";
    DataModel* _model;
    WalletTable _walletTable;
};

#endif // WALLETSCREEN_H
