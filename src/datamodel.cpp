#include "datamodel.h"

void DataModel::postRequest(QJsonObject req)
{
    req["jsonrpc"] = "1.0";
    QByteArray postData = QJsonDocument(req).toJson(QJsonDocument::Compact);

    //qInfo() << QString(postData);

    QNetworkAccessManager * mgr = new QNetworkAccessManager();

    QObject::connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinish(QNetworkReply*)));
    QObject::connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));

    remote = QUrl(QString("http://%1:%2").arg(remoteAddress).arg(remotePort));
    QNetworkRequest request(remote);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    mgr->post(request, postData);
}

QString DataModel::constructCommitCommand(QStringList commits) {
    QString c = "%1";

    if(commits.size() > 255) {
        return "varint not implemented";
    }

    QString raw = "0100000000" + QString("%1").arg(commits.size(), 2, 16, QLatin1Char('0'));
    for(size_t i = 0; i < commits.size(); i++) {
        raw += QString("4A01000000000000220020") + commits[i];
    }
    raw += "00000000";

    c = c.arg(raw);

    return c;
}
