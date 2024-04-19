#ifndef RESTAPI_H
#define RESTAPI_H

#include "restapi_global.h"
#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class RESTAPI_EXPORT Restapi : public QObject
{
    Q_OBJECT
public:
    Restapi();
    //test
    void getAllAccounts();
    void postCustomer(QJsonObject jsonObj);
    //real
    //takes serial and pin. returns token on success. on error return false.
    void postLogin(QJsonObject jsonObj);
    //takes serial. returns cu_id.
    void getAccountId(QJsonObject jsonObj);
    //takes cu_id. returns ac_id, balance and credit.
    void getAccountBalance(QJsonObject jsonObj);
    //takes ac_id, start, stop. returns end-start amont of transactions.
    void getTransactions(QJsonObject jsonObj);
    //takes type, newAmount, cu_id, transaction and ac_id. returns query.
    void postWithdraw(QJsonObject jsonObj);
    //set this token to the token got from postLogin().
    QString token;
signals:
    void replySet(QString lastReply);

private slots:
    void getResponse(QNetworkReply *reply);
    void postResponse(QNetworkReply *reply);

private:
    void getResponseEnd(QString responseData);
    QJsonArray getParserJson(QNetworkReply *reply);
    QString getParserQstring(QJsonArray json_array);
    void getConnect(QString site_url);

    void postConnect(QString site_url, QJsonObject jsonObj);

    std::vector<QString> targets;
    QJsonObject jsonObj;
    QNetworkAccessManager *apiManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // RESTAPI_H
