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
    api->postLogin("testi20","1234");
    //api->getAllAccounts();

}

void MainWindow::setUiText(QString lastReply)
{
    if(coolThing){
        /*
     auto result = lastReply.split(", ");
    ui->textAccounts->setText(result[2]);
*/
        QString oldText;
        ui->textAccounts->setText("");
        auto result = lastReply.split(", ");
        for (int i = 0; i<result.length()/2; i++){
            qDebug() << result[i] +  result[(result.length()/2)+i];
            oldText = ui->textAccounts->toPlainText();
            ui->textAccounts->setText(oldText + "\n" + result[i] + ", " + result[(result.length()/2)+i]);
        }
    }

    else{
    ui->textAccounts->setText(lastReply);
    api->token = lastReply;
    }
}



void MainWindow::on_pushButton_2_clicked()
{
    /*
    QJsonObject jsonObj;
    jsonObj.insert("serial","testi20");
    api->getAccountId(jsonObj);
*/
}


void MainWindow::on_pushButton_3_clicked()
{
    /*
    QJsonObject jsonObj;
    jsonObj.insert("type","balance");
    jsonObj.insert("newAmount",1900);
    jsonObj.insert("cu_id",3);
    jsonObj.insert("transaction",100);
    jsonObj.insert("ac_id",1);
    api->postWithdraw(jsonObj);
_*/

    coolThing = true;
    api->getTransactions(1,0,5);
/*
    QJsonObject jsonObj;
    jsonObj.insert("id",1);
    jsonObj.insert("start",0);
    jsonObj.insert("stop",5);
    api->getTransactions(jsonObj);
    */
}

