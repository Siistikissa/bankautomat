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
    api->getAllAccounts();
}

void MainWindow::setUiText()
{
    ui->textAccounts->setText(api->lastReply);
}



void MainWindow::on_pushButton_2_clicked()
{
    QJsonObject jsonObj;
    jsonObj.insert("fname","Hullu");
    jsonObj.insert("lname","Koodari");

    api->postCustomer(jsonObj);
}

