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
    void getSerial();
    void getPin();
    void getAccount(QString accountId);
    void getTransactions();
    void postWithdraw(QJsonObject jsonObj);
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

    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // RESTAPI_H
