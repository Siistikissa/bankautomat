#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    beep.setSource(QUrl::fromLocalFile("C:\\projektit\\pankkiautomaatti\\SPL_Group8\\bankautomat_exe\\bankautomat\\beep.wav"));
    beep.setVolume(1.0);
    lowbeep.setSource(QUrl::fromLocalFile("C:\\projektit\\pankkiautomaatti\\SPL_Group8\\bankautomat_exe\\bankautomat\\lowbeep.wav"));
    lowbeep.setVolume(1.0);
    connect(ui->KuittiButton, &QPushButton::clicked, this, &MainWindow::createKuitti);
    vaihe1();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::vaihe1()
{
    qDebug()<<"vaihe1()..";
    ui->lineEdit->setText("         Syötä kortti");
    ui->btnA->setText("");
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}

void MainWindow::vaihe2()
{
    qDebug()<<"vaihe2()..";
    ui->btnA->setText("Keskeytä tapahtuma");
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::vaihe1);
    createPinUI();
    ui->lineEdit->setText("         Syötä PIN-koodi, 3 yritystä jäljellä");
}

void MainWindow::vaihe3()
{
    qDebug()<<"vaihe3()..";
    ui->lineEdit->setText("         Valitse toiminto");
    ui->btnB->setText("Tilin saldo");
    ui->btnC->setText("Tilitapahtumat");
    ui->btnD->setText("Nosto");
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::naytaSaldo);
    connect(ui->btnC, &QPushButton::clicked, this, &MainWindow::naytaTapahtumat);
    connect(ui->btnD, &QPushButton::clicked, this, &MainWindow::nostaRahaa);
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}

void MainWindow::naytaSaldo()
{
    qDebug()<<"naytaSaldo()..";
    ui->lineEdit->setText("         Tilin saldo:");
    ui->btnB->setText("Takaisin");
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::vaihe3);
    ui->btnC->setText("");
    ui->btnD->setText("");
}


void MainWindow::naytaTapahtumat()
{
    qDebug()<<"naytaTapahtumat()..";
    ui->lineEdit->setText("         Tilitapahtumat:");
    ui->btnB->setText("Takaisin");
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::vaihe3);
    ui->btnC->setText("Siirry vanhempiin");
    ui->btnD->setText("Siirry uudempiin");
}


void MainWindow::nostaRahaa()
{
    qDebug()<<"nostaRahaa()..";
    ui->lineEdit->setText("         Valitse summa");
    ui->btnB->setText("Takaisin");
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::vaihe3);
    ui->btnC->setText("20€");
    ui->btnD->setText("40€");
    ui->btnE->setText("60€");
    ui->btnF->setText("90€");
    ui->btnG->setText("140€");
    ui->btnH->setText("240€");
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

void MainWindow::on_RFIDButton_clicked()
{
    qDebug()<<"*kortti syötetty koneeseen..";
    RFIDpressed = true;
    vaihe2();
}

void MainWindow::on_PINUIButton_clicked()
{
    qDebug()<<"*PIN syötetty oikein..";
    vaihe3();
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

