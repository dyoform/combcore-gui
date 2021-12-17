#include "datamodel.h"

void DataModel::postRequest(QJsonObject req)
{
    QByteArray postData = QJsonDocument(req).toJson(QJsonDocument::Compact);

    //qInfo() << QString(postData);

    QNetworkAccessManager * mgr = new QNetworkAccessManager();

    QObject::connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onFinish(QNetworkReply*)));
    QObject::connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));

    QNetworkRequest request(remote);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    mgr->post(request, postData);
}
