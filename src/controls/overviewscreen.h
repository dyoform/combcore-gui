#ifndef OVERVIEWSCREEN_H
#define OVERVIEWSCREEN_H

#include <QObject>
#include <qqml.h>
#include <QClipboard>
#include <QGuiApplication>

#include "datamodel.h"
#include "pendingtable.h"

class OverviewScreen : public QObject
{
    Q_OBJECT
    Q_PROPERTY(PendingTable* pendingTable READ pendingTable CONSTANT)
    Q_PROPERTY(QString height READ height NOTIFY changed)
    Q_PROPERTY(QString btcHeight READ btcHeight NOTIFY changed)
    Q_PROPERTY(QString btcKnownHeight READ btcKnownHeight NOTIFY changed)
    Q_PROPERTY(QString commits READ commits NOTIFY changed)
    Q_PROPERTY(QString status READ status NOTIFY changed)
    Q_PROPERTY(QString btcStatus READ btcStatus NOTIFY changed)
    Q_PROPERTY(QString network READ network NOTIFY networkChanged)
    QML_ELEMENT
public:
    explicit OverviewScreen(QObject *parent = nullptr);
    void inject(DataModel* model) {
        _model = model;
        _pendingTable.inject(model);
        connect(_model, SIGNAL(gotData(QString, QJsonObject)), this, SLOT(gotData(QString, QJsonObject)));
        connect(_model, SIGNAL(connectedChanged(bool)), this, SLOT(connectedChanged(bool)));
    }
    PendingTable* pendingTable() {return &_pendingTable;}
    QString height() {return QString("%1").arg(_comb_height);}
    QString btcHeight() {return QString("%1").arg(_btc_height);}
    QString btcKnownHeight() {return QString("%1").arg(_btc_known_height);}
    QString commits() {return QString("%1").arg(_commits);}
    QString status() {
        if(!_model->connected)
            return "Disconnected";
        return _status;
    }
    QString btcStatus() {
        if(_btc_known_height == 0) {
            return QString("Unknown");
        }
        if(_btc_known_height > _btc_height) {
            return QString("Syncing");
        }
        if(_btc_known_height == _btc_height) {
            return QString("Idle");
        }
    }
    QString network() {return _network;}
public slots:
    void gotData(QString id, QJsonObject data) {
        if(id != "getStatus" && id != "checkClaim" && id != "checkSignature" && id != "getCommits") {
            return;
        }
        if(data["error"].isString() && data["error"].toString() != "") {
            qInfo() << data["error"].toString();
            return;
        }

        if(id == "getStatus") {
            data = data["result"].toObject();
            _comb_height = data["COMBHeight"].toInt();
            _btc_height = data["BTCHeight"].toInt();
            _btc_known_height = data["BTCKnownHeight"].toInt();
            _commits = data["Commits"].toInt();
            _status = data["Status"].toString();
            if(data["Network"].toString() != _network) {
                _network = data["Network"].toString();
                emit networkChanged();
            }
        }

        if(id == "checkClaim") {
            auto a = data["result"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _model->addCommit(new Commit(TYPE_CLAIM, a[i].toString()));
            }
        }

        if(id == "checkSignature") {
            auto a = data["result"].toArray();
            for(int i = 0; i < a.size(); i++) {
                _model->addCommit(new Commit(TYPE_SIGNATURE, a[i].toString()));
            }
        }

        if(id == "getCommits") {
            auto a = data["result"].toArray();
            QStringList commits;
            for(int i = 0; i < a.size(); i++) {
                commits.append(a[i].toString());
            }
            copyCommand(commits);
        }



        emit changed();
    }
    void connectedChanged(bool connected) {
        if(!connected) {
            _btc_known_height = 0;
        }
        emit changed();
    }

    void getCommand() {
        QJsonObject j;
        j["id"] = "getCommits";
        j["method"] = "Control.CommitAddresses";
        QJsonArray a;
        QJsonArray b;
        for(int i = 0; i < _model->pending_commits.size(); i++) {
            b.append(_model->pending_commits[i]->ID());
        }
        a.append(b);
        j["params"] = a;
        _model->postRequest(j);
    }

    void clear() {
        _model->clearCommits();
    }

    void copyCommand(QStringList commits) {
        QClipboard *c = QGuiApplication::clipboard();
        c->setText(_model->constructCommitCommand(commits));
    }
private:
    uint64_t _comb_height = 0;
    uint64_t _btc_height = 0;
    uint64_t _btc_known_height = 0;
    uint64_t _commits = 0;
    QString _status = "Unknown";
    QString _network = "mainnet";
    DataModel* _model;
    PendingTable _pendingTable;

signals:
    void changed();
    void networkChanged();
};

#endif // OVERVIEWSCREEN_H
