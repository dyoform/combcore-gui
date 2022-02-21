#ifndef DATAMODEL_H
#define DATAMODEL_H
#include <QObject>
#include <QString>
#include <QTimer>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QHttpPart>
#include <QFile>
#include <QSettings>

#include <memory>
#include <vector>

#include "construct.h"
#include "commit.h"
#include "key.h"
#include "stack.h"
#include "transaction.h"
#include "decider.h"
#include "merklesegment.h"

class DataModel : public QObject {
    Q_OBJECT
public:
    bool connected = false;
    QString remoteAddress;
    uint16_t remotePort;
    QStringList output;
    std::vector<std::unique_ptr<Construct>> constructs;
    std::vector<std::unique_ptr<Commit>> pending_commits;
    explicit DataModel() {
        loadSettings();
        statusSync.setInterval(100);
        walletSync.setInterval(5000);
        connect(&statusSync,SIGNAL(timeout()),this,SLOT(getStatus()));
        connect(&walletSync,SIGNAL(timeout()),this,SLOT(getWallet()));
        statusSync.start();
        walletSync.start();
    }
    void addConstruct(Construct* construct) {
        constructs.emplace_back(std::unique_ptr<Construct>(construct));
        emit dataChanged();
    }

    void appendOutput(QString out) {
        output.append(out.trimmed().split("\n", Qt::SkipEmptyParts));
        emit dataChanged();
    }

    void checkSignature(QStringList signature) {
        QJsonObject j;
        j["id"] = "checkSignature";
        j["method"] = "Control.CheckAddresses";
        QJsonArray a;
        QJsonArray b;
        for(int i = 0; i < signature.length(); i++) {
            b.append(signature[i]);
        }
        a.append(b);
        j["params"] = a;
        postRequest(j);
    }

    void checkClaim(QString address) {
        QJsonObject j;
        j["id"] = "checkClaim";
        j["method"] = "Control.CheckAddresses";
        QJsonArray a;
        QJsonArray b;
        b.append(address);
        a.append(b);
        j["params"] = a;
        postRequest(j);
    }


    void addCommit(Commit* commit) {
        for(int i = 0; i < pending_commits.size(); i++) {
           if(*(pending_commits[i].get()) == *commit) {
               return;
           }
        }
         pending_commits.emplace_back(std::unique_ptr<Commit>(commit));
        emit dataChanged();
    }
    void clearCommits() {
        pending_commits.clear();
        getWallet();
    }
    bool haveConstruct(QString id) {
        for(size_t i = 0; i < constructs.size(); i++) {
            if(constructs[i]->ID() == id) {
                return true;
            }
        }
        return false;
    }


    void loadSettings() {
        QSettings settings;
        remoteAddress = settings.value("remoteAddress", "127.0.0.1").toString();
        remotePort = settings.value("remotePort", QVariant(uint(2211))).toUInt();
    }
    void saveSettings() {
        QSettings settings;
        settings.setValue("remoteAddress", remoteAddress);
        settings.setValue("remotePort", remotePort);
    }
    QString constructCommitCommand(QStringList commits);
    void postRequest(QJsonObject req);
public slots:
    void onFinish(QNetworkReply *rep) {
        if(rep->error() != 0) {
            setConnected(false);
            return;
        }
        setConnected(true);

        auto raw = rep->readAll();
        QJsonObject j = QJsonDocument().fromJson(raw).object();
        auto id = j["id"].toString();
        emit gotData(id, j);
    }
    void getStatus() {
        QJsonObject j;
        j["id"] = "getStatus";
        j["method"] = "Control.GetStatus";
        j["params"] = QJsonArray();
        postRequest(j);
    }
    void getWallet() {
        QJsonObject j;
        j["id"] = "getWallet";
        j["method"] = "Control.GetWallet";
        j["params"] = QJsonArray();
        postRequest(j);
    }
    void update() {
        emit dataChanged();
    }

private:
    QTimer statusSync;
    QTimer walletSync;
    QUrl remote;
    void setConnected(bool nowConnected) {
        if(connected != nowConnected) {
            connected = nowConnected;
            emit connectedChanged(nowConnected);
        }
    }
signals:
    void dataChanged();
    void connectedChanged(bool);
    void gotData(QString, QJsonObject);
};

#endif // DATAMODEL_H
