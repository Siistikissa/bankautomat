#include "restapi.h"

Restapi::Restapi() {

}

void Restapi::getAllAccounts()
{
    getConnect("http://localhost:3000/accounts");
    targets.push_back("balance");
    targets.push_back("credit");
    targets.push_back("ac_id");
    connect(apiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));

}

void Restapi::postCustomer(QJsonObject jsonObj)
{
    postConnect("http://localhost:3000/Customers", jsonObj);
    connect(apiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(postResponse(QNetworkReply*)));

}

void Restapi::postLogin(QString serial, QString pin)
{
    jsonObj.insert("serial", serial);
    jsonObj.insert("pin", pin);
    postConnect("http://localhost:3000/login", jsonObj);
    connect(apiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(postResponse(QNetworkReply*)));
}

void Restapi::getAccountId(QString serial)
{
    jsonObj.insert("serial", serial);
    postConnect("http://localhost:3000/cards", jsonObj);
    targets.push_back("ca_id");
    connect(apiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}

void Restapi::getAccountBalance(int cu_id)
{
    jsonObj.insert("cu_id", cu_id);
    postConnect("http://localhost:3000/accounts", jsonObj);
    targets.push_back("ac_id");
    targets.push_back("balance");
    targets.push_back("credit");
    connect(apiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}

void Restapi::getTransactions(int ac_id, int start, int stop)
{
    jsonObj.insert("ac_id", ac_id);
    jsonObj.insert("start", start);
    jsonObj.insert("stop", stop);
    qDebug() << "jsonObj : " <<jsonObj;
    postConnect("http://localhost:3000/transactions", jsonObj);
    targets.push_back("transaction");
    targets.push_back("tr_date");
    connect(apiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getResponse(QNetworkReply*)));
}

void Restapi::postWithdraw(QString type, int newAmount, int cu_id, int transaction, int ac_id)
{
    jsonObj.insert("type", type);
    jsonObj.insert("newAmount", newAmount);
    jsonObj.insert("cu_id", cu_id);
    jsonObj.insert("transaction", transaction);
    jsonObj.insert("ac_id", ac_id);
    postConnect("http://localhost:3000/transactions/withdraw", jsonObj);
    connect(apiManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(postResponse(QNetworkReply*)));
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
    for(auto iter = jsonObj.begin(); iter != jsonObj.end();){
        jsonObj.erase(iter);
    }
    reply->deleteLater();
    apiManager->deleteLater();
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
    qDebug() << "json array : " <<json_array;
    for(auto i = targets.begin(); i != targets.end(); i++){
        for (const QJsonValue &value : json_array) {
            qDebug() << "value : " <<value;
            QJsonObject json_obj = value.toObject();

            if (i != targets.begin() && i != targets.end() || value == json_array[1]){
                data.append(", ");
            }
            QVariant variant = json_obj[*i].toVariant();
            data.append(variant.value<QString>());
            qDebug() << "data : " <<data;
        }
    }

    //qDebug() << "QString data : " << data;
    return data;
}

void Restapi::getConnect(QString site_url)
{
    //QString site_url="http://localhost:3000/accounts";
    QNetworkRequest request((site_url));

    apiManager = new QNetworkAccessManager(this);

    reply = apiManager->get(request);
    //qDebug() << "Reply : " << reply;
}

void Restapi::postConnect(QString site_url, QJsonObject jsonObj)
{
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader(QByteArray("authorization"), QByteArray("token " + token.toUtf8()));
    apiManager = new QNetworkAccessManager(this);
    reply = apiManager->post(request, QJsonDocument(jsonObj).toJson());
}

void Restapi::postResponse(QNetworkReply *reply)
{
    response_data=reply->readAll();
    emit replySet(response_data);
    //qDebug()<<response_data;
    for(auto iter = jsonObj.begin(); iter != jsonObj.end();){
        jsonObj.erase(iter);
    }
    qDebug() << "after erase : " << jsonObj;
    reply->deleteLater();
    apiManager->deleteLater();
}
