#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir directory("../bankautomat/");
    QString pathToBeep = directory.absoluteFilePath("beep.wav");
    QString pathToLowBeep = directory.absoluteFilePath("lowbeep.wav");
    beep.setSource(QUrl::fromLocalFile(pathToBeep));
    beep.setVolume(1.0);
    lowbeep.setSource(QUrl::fromLocalFile(pathToLowBeep));
    lowbeep.setVolume(1.0);
    connect(ui->KuittiButton, &QPushButton::clicked, this, &MainWindow::createKuitti);
    startScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startScreen()
{
    qDebug()<<"startScreen()..";
    ui->lineEdit->setText("         Syötä kortti");
    clearUiButtons();
}

void MainWindow::pinScreen()
{
    qDebug()<<"pinScreen()..";
    ui->btnA->setText("Keskeytä tapahtuma");
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::startScreen);
    createPinUI();
    ui->lineEdit->setText("Syötä PIN-koodi, 3 yritystä jäljellä");
}

void MainWindow::mainScreen()
{
    disconnectAllFunctions();
    qDebug()<<"mainScreen()..";
    ui->lineEdit->setText("         Valitse toiminto");
    ui->btnB->setText("Tilin saldo");
    ui->btnC->setText("Tilitapahtumat");
    ui->btnD->setText("Nosto");
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::showBalance);
    connect(ui->btnC, &QPushButton::clicked, this, &MainWindow::showTransactions);
    connect(ui->btnD, &QPushButton::clicked, this, &MainWindow::showWithdraw);
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}

void MainWindow::showBalance()
{
    disconnectAllFunctions();
    connect(api, &Restapi::replySet, this, &MainWindow::setUiTextBalance);
    QString mockid = "1";
    api->getAccount(mockid);
    qDebug()<<"showBalance()..";
    //ui->lineEdit->setText("         Tilin saldo:");
    ui->btnB->setText("Takaisin");
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::mainScreen);
    ui->btnC->setText("");
    ui->btnD->setText("");
}


void MainWindow::showTransactions()
{
    disconnectAllFunctions();
    qDebug()<<"showTransactions()..";
    ui->lineEdit->setText("         Tilitapahtumat:");
    ui->btnB->setText("Takaisin");
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::mainScreen);
    ui->btnC->setText("Siirry vanhempiin");
    ui->btnD->setText("Siirry uudempiin");
}


void MainWindow::showWithdraw()
{
    disconnectAllFunctions();
    qDebug()<<"showWithdraw()..";
    ui->lineEdit->setText("Valitse summa");
    ui->btnB->setText("Takaisin");
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::mainScreen);
    ui->btnC->setText("20€");
    ui->btnD->setText("40€");
    ui->btnE->setText("60€");
    ui->btnF->setText("90€");
    ui->btnG->setText("140€");
    ui->btnH->setText("240€");
}

void MainWindow::clearUiButtons()
{
    ui->btnA->setText("");
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}
void MainWindow::setUiTextBalance(QString lastReply)
{
    ui->lineEdit->setText(lastReply);
}

void MainWindow::createPinUI()
{
    PinUI* PinWindow = new PinUI;
    PinWindow->show();
}

void MainWindow::createKuitti()
{
    Kuitti* KuittiWindow = new Kuitti;
    KuittiWindow->show();
}
void MainWindow::createRfid() {
    Rfid* RfidWindow = new Rfid;
    RfidWindow->show();
}


void MainWindow::on_RFIDButton_clicked()
{
    qDebug()<<"*kortti syötetty koneeseen..";
    RFIDpressed = true;
    pinScreen();
}

void MainWindow::on_PINUIButton_clicked()
{
    qDebug()<<"*PIN syötetty oikein..";
    mainScreen();
}

void MainWindow::on_KuittiButton_clicked()
{
    qDebug()<<"Tulostetaan kuitti..";
}

void MainWindow::on_btnA_clicked()
{
    beep.play();
    qDebug()<<"A-toimintoa painettu..";
}

void MainWindow::on_btnB_clicked()
{
    beep.play();
    qDebug()<<"B-toimintoa painettu..";
}

void MainWindow::on_btnC_clicked()
{
    beep.play();
    qDebug()<<"C-toimintoa painettu..";
}

void MainWindow::on_btnD_clicked()
{
    beep.play();
    qDebug()<<"D-toimintoa painettu..";
}

void MainWindow::on_btnE_clicked()
{
    beep.play();
    qDebug()<<"E-toimintoa painettu..";
}

void MainWindow::on_btnF_clicked()
{
    beep.play();
    qDebug()<<"F-toimintoa painettu..";
}

void MainWindow::on_btnG_clicked()
{
    beep.play();
    qDebug()<<"G-toimintoa painettu..";
}

void MainWindow::on_btnH_clicked()
{
    beep.play();
    qDebug()<<"H-toimintoa painettu..";
}

void MainWindow::disconnectAllFunctions()
{
    disconnect(ui->btnB, &QPushButton::clicked, this, &MainWindow::showBalance);
    disconnect(ui->btnC, &QPushButton::clicked, this, &MainWindow::showTransactions);
    disconnect(ui->btnD, &QPushButton::clicked, this, &MainWindow::showWithdraw);
    disconnect(ui->btnB, &QPushButton::clicked, this, &MainWindow::mainScreen);
}

