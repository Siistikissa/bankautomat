#include "restapi.h"

Restapi::Restapi() {

}

void Restapi::getAllAccounts()
{
    QString site_url="http://localhost:3000/accounts";
    QNetworkRequest request((site_url));

    getManager = new QNetworkAccessManager(this);

    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getAccountsResponse(QNetworkReply*)));
    reply = getManager->get(request);
    qDebug() << "Reply : " << reply;
}

void Restapi::postCustomer(QJsonObject jsonObj)
{
    QString site_url="http://localhost:3000/Customers";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(postCustomerResponse(QNetworkReply*)));

    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Restapi::postCustomerResponse(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
}

void Restapi::getAccountsResponse(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString account;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        account+=QString::number(json_obj["ac_id"].toInt())+", "+json_obj["balance"].toString()+","
                   +json_obj["credit"].toString()+","+QString::number(json_obj["cu_id"].toInt())+","+QString::number(json_obj["ca_id"].toInt())+"\r";
    }
    lastReply = account;
    emit replySet(account);
    reply->deleteLater();
    getManager->deleteLater();
}
