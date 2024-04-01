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
    QString lastReply;
    void getAllAccounts();
    void postCustomer(QJsonObject jsonObj);

signals:
    void replySet(QString lastReply);

private slots:
    void postCustomerResponse(QNetworkReply *reply);
    void getAccountsResponse(QNetworkReply *reply);

private:
    QNetworkAccessManager *getManager;
    QNetworkAccessManager *postManager;
    QNetworkReply *reply;
    QByteArray response_data;
};

#endif // RESTAPI_H
