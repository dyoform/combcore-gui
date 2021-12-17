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
    std::vector<std::unique_ptr<Construct>> constructs;
    std::vector<std::unique_ptr<Commit>> pending_commits;
    explicit DataModel() {
        remote = QUrl("http://10.0.0.2:2211");
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
    void postRequest(QJsonObject req);
public slots:
    void onFinish(QNetworkReply *rep) {
        if(rep->error() != 0) {
            connected = false;
            emit connectedChanged(false);
            return;
        } else if (connected == false) {
            connected = true;
            emit connectedChanged(true);
        }
        auto raw = rep->readAll();
        QJsonObject j = QJsonDocument().fromJson(raw).object();
        auto id = j["id"].toString();
        emit gotData(id, j);
    }
    void getStatus() {
        QJsonObject j;
        j["jsonrpc"] = "1.0";
        j["id"] = "getStatus";
        j["method"] = "Control.GetStatus";
        j["params"] = QJsonArray();
        postRequest(j);
    }
    void syncWallet() {
        QJsonObject j;
        j["jsonrpc"] = "1.0";
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
signals:
    void dataChanged();
    void connectedChanged(bool);
    void gotData(QString, QJsonObject);
};

#endif // DATAMODEL_H
