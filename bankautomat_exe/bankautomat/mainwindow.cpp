#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bankui.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->PINUIButton, &QPushButton::clicked, this, &MainWindow::createBankUI);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_RFIDButton_clicked()
{
    qDebug()<< "RFID pressed";
}


void MainWindow::on_PINUIButton_clicked()
{
    qDebug()<< "PINUI pressed";
    qDebug()<< "BankUI started";

}

void MainWindow::createBankUI()
{
    bankUI* BankWindow = new bankUI;
    BankWindow->show();
}

