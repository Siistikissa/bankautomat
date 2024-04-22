#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setup paths to sounds
    QDir directory("../bankautomat/");
    QString pathToBeep = directory.absoluteFilePath("beep.wav");
    QString pathToLowBeep = directory.absoluteFilePath("lowbeep.wav");
    beep.setSource(QUrl::fromLocalFile(pathToBeep));
    beep.setVolume(1.0);
    lowbeep.setSource(QUrl::fromLocalFile(pathToLowBeep));
    lowbeep.setVolume(1.0);
    //connect debug buttons
    connect(ui->KuittiButton, &QPushButton::clicked, this, &MainWindow::createKuitti);
    connect(ui->RFIDButton_2, &QPushButton::clicked, this, &MainWindow::createRfid);
    connect(api, &Restapi::replySet, this, &MainWindow::parseApiReply);
    //connect rfid reader and start the aplication
    connect(rfid, &Rfid::cardNumber, this, &MainWindow::pinScreen);
    langueage = 0;
    startScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startScreen()
{
    qDebug()<<"startScreen()..";
    ui->lineEdit->setText(dictionary["Insert card"][langueage]);
    clearUiButtons();
}

void MainWindow::pinScreen(QString cNum)
{
    qDebug()<<"pinScreen()..";
    serial = cNum;
    ui->btnA->setText(dictionary["Abort transaction"][langueage]);
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::startScreen);
    createPinUI();
    ui->lineEdit->setText(dictionary["Insert pin"][langueage] + "3" + dictionary["Tries left"][langueage] );
}

void MainWindow::mainScreen()
{
    disconnectAllFunctions();
    qDebug()<<"mainScreen()..";
    ui->lineEdit->setText(dictionary["Choose action"][langueage]);
    ui->btnB->setText(dictionary["Account balance"][langueage]);
    ui->btnC->setText(dictionary["Account transactions"][langueage]);
    ui->btnD->setText(dictionary["Withdrawal"][langueage]);
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
    api->getAccountBalance(cu_id);
    apiState = "accountBalance";
    qDebug()<<"showBalance()..";
    ui->btnB->setText(dictionary["Back"][langueage]);
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::mainScreen);
    ui->btnC->setText("");
    ui->btnD->setText("");
}


void MainWindow::showTransactions()
{
    disconnectAllFunctions();
    api->getTransactions(ac_id, 0, 5); //TODO: add logic to start and stop
    qDebug()<<"showTransactions()..";
    ui->btnB->setText(dictionary["Back"][langueage]);
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::mainScreen);
    ui->btnC->setText(dictionary["Show older"][langueage]);
    ui->btnD->setText(dictionary["Show newer"][langueage]);
}


void MainWindow::showWithdraw()
{
    disconnectAllFunctions();
    qDebug()<<"showWithdraw()..";
    ui->lineEdit->setText("Valitse summa");
    ui->btnB->setText(dictionary["Back"][langueage]);
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
void MainWindow::parseApiReply(QString lastReply)
{
    if(apiState == "login"){
        api->token = lastReply;
        api->getAccountId(serial);
        apiState = "accountId";
    }
    else if(apiState == "accountId"){
        cu_id = lastReply.toInt();
        mainScreen();
    }
    else if(apiState == "accountBalance"){
        //parse lastreply to 3
        auto result = lastReply.split(", ");
        ac_id = result[0].toInt();
        balance = result[1];
        credit = credit[2];
        if(credit == "0"){
            type = "balance";
        }
        else{
            type = "credit";
        }
        if(type == "balance"){
            ui->lineEdit->setText(dictionary["Account balance"][langueage] + balance);

        }
        else if(type == "credit"){
            ui->lineEdit->setText(dictionary["Account balance"][langueage] + credit);


        }
    }
    else if(apiState == "transactions"){
        ui->lineEdit->setText(dictionary["Account transactions"][langueage] + "\n");
        QString oldText;
        auto result = lastReply.split(", ");
        for (int i = 0; i<result.length()/2; i++){
            oldText = ui->lineEdit->text();
            transactionsVector.push_back( result[i] + ", " + result[(result.length()/2)+i]);
            ui->lineEdit->setText(oldText + result[i] + ", " + result[(result.length()/2)+i] + "\n");
        }
    }
    else if(apiState == "withdraw"){

    }
}

void MainWindow::checkPassword(QString tryPin)
{
    pin = tryPin;
    api->postLogin(serial,pin);
}

void MainWindow::clearApiData()
{
    serial.clear();
    pin.clear();
    type.clear();
    balance.clear();
    credit.clear();
    transactionsVector.clear();
    cu_id = 0 ;
    ac_id = 0;
    newAmount = 0;
    start = 0;
    stop = 0;
    transaction = 0;

}

void MainWindow::createPinUI()
{
    PinUI* PinWindow = new PinUI;
    connect(PinWindow, &PinUI::sendPin, this, &MainWindow::checkPassword);
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
    //pinScreen();
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

