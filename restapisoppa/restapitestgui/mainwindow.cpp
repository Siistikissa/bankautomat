#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(api, &Restapi::replySet, this, &MainWindow::setUiText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("serial","testi20");
    jsonObj.insert("pin","1234");

    api->postLogin(jsonObj);
    //api->getAllAccounts();
}

void MainWindow::setUiText(QString lastReply)
{
    ui->textAccounts->setText(lastReply);
    api->token = lastReply;
}



void MainWindow::on_pushButton_2_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("serial","testi20");
    api->getAccountId(jsonObj);
}


void MainWindow::on_pushButton_3_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("type","balance");
    jsonObj.insert("newAmount",1900);
    jsonObj.insert("cu_id",3);
    jsonObj.insert("transaction",100);
    jsonObj.insert("ac_id",1);
    api->postWithdraw(jsonObj);
    /*
    QJsonObject jsonObj;
    jsonObj.insert("cu_id",3);
    api->getAccountBalance(jsonObj);
*/
/*
    QJsonObject jsonObj;
    jsonObj.insert("id",1);
    jsonObj.insert("start",0);
    jsonObj.insert("stop",5);
    api->getTransactions(jsonObj);
    */
}

