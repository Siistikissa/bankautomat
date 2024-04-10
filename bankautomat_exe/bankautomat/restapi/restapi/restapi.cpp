#include "restapi.h"

Restapi::Restapi() {

}

void Restapi::getAllAccounts()
{
    getConnect("http://localhost:3000/accounts");
    targets.push_back("balance");
    targets.push_back("credit");
    targets.push_back("ac_id");
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));

}

void Restapi::postCustomer(QJsonObject jsonObj)
{
    postConnect("http://localhost:3000/Customers", jsonObj);
    connect(postManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(postResponse(QNetworkReply*)));

}

void Restapi::getSerial()
{
    getConnect("http://localhost:3000/accounts");
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}

void Restapi::getPin()
{
    getConnect("http://localhost:3000/accounts");
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}

void Restapi::getAccount(QString accountId)
{
    getConnect("http://localhost:3000/accounts/"+accountId);
    targets.push_back("balance");
    targets.push_back("credit");
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}

void Restapi::getTransactions()
{
    getConnect("http://localhost:3000/accounts");
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}

void Restapi::postWithdraw(QJsonObject jsonObj)
{
    postConnect("http://localhost:3000/Customers", jsonObj);
    connect(getManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}


void Restapi::getResponse(QNetworkReply *reply)
{
    QJsonArray json_array = getParserJson(reply);
    QString data = getParserQstring(json_array);
    getResponseEnd(data);
}

void Restapi::getResponseEnd(QString responseData)
{
    emit replySet(responseData);
    reply->deleteLater();
    getManager->deleteLater();
    targets.clear();
}

QJsonArray Restapi::getParserJson(QNetworkReply *reply)
{
    response_data=reply->readAll();
    //qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    return json_array;
}

QString Restapi::getParserQstring(QJsonArray json_array)
{
    QString data;
    //parsing json to qstring
    for(auto i = targets.begin(); i != targets.end(); i++){
        for (const QJsonValue &value : json_array) {
            QJsonObject json_obj = value.toObject();

            if (i != targets.begin() && i != targets.end()){
                data.append(", ");
            }
            QVariant variant = json_obj[*i].toVariant();
            data.append(variant.value<QString>());
        }
    }

    //qDebug() << "QString data : " << data;
    return data;
}

void Restapi::getConnect(QString site_url)
{
    //QString site_url="http://localhost:3000/accounts";
    QNetworkRequest request((site_url));

    getManager = new QNetworkAccessManager(this);

    reply = getManager->get(request);
    //qDebug() << "Reply : " << reply;
}

void Restapi::postConnect(QString site_url, QJsonObject jsonObj)
{
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    postManager = new QNetworkAccessManager(this);
    reply = postManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Restapi::postResponse(QNetworkReply *reply)
{
    response_data=reply->readAll();
    //qDebug()<<response_data;
    reply->deleteLater();
    postManager->deleteLater();
}
