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

class DataModel : public QObject {
    Q_OBJECT
public:
    bool connected = false;
    QString remoteAddress;
    uint16_t remotePort;
    std::vector<std::unique_ptr<Construct>> constructs;
    std::vector<std::unique_ptr<Commit>> pending_commits;
    explicit DataModel() {
        loadSettings();
        sync.setInterval(100);
        connect(&sync,SIGNAL(timeout()),this,SLOT(getStatus()));
        sync.start();
    }
    void addConstruct(Construct* construct) {
        constructs.emplace_back(std::unique_ptr<Construct>(construct));
        emit dataChanged();
    }
    void addCommit(Commit* commit) {
        pending_commits.emplace_back(std::unique_ptr<Commit>(commit));
        emit dataChanged();
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
    QString constructCommitCommand();
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
    void syncWallet() {
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
    QTimer sync;
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
