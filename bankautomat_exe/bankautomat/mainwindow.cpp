#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    //setup paths to sounds
    QDir directory("../");
    QPixmap flag_of_uk = directory.absoluteFilePath("Flag_of_the_United_Kingdom.png");
    QIcon englishIcon(flag_of_uk);
    ui->english->setIcon(englishIcon);
    QPixmap flag_of_finland = directory.absoluteFilePath("Flag_of_Finland.png");
    QIcon finnishIcon(flag_of_finland);
    ui->finnish->setIcon(finnishIcon);
    QPixmap flag_of_sweden = directory.absoluteFilePath("Flag_of_Sweden.png");
    QIcon swedishIcon(flag_of_sweden);
    ui->swedish->setIcon(swedishIcon);
    QString pathToBeep = directory.absoluteFilePath("beep.wav");
    QString pathToLowBeep = directory.absoluteFilePath("lowbeep.wav");
    QString pathToPrinttaus = directory.absoluteFilePath("printtaus.wav");
    beep.setSource(QUrl::fromLocalFile(pathToBeep));
    beep.setVolume(1.0);
    lowbeep.setSource(QUrl::fromLocalFile(pathToLowBeep));
    lowbeep.setVolume(1.0);
    printtaus.setSource(QUrl::fromLocalFile(pathToPrinttaus));
    printtaus.setVolume(1.0);
    //connect debug buttons
    connect(ui->KuittiButton, &QPushButton::clicked, this, &MainWindow::createKuitti);
    connect(ui->SerialButton, &QPushButton::clicked, this, &MainWindow::createRfid);
    connect(api, &Restapi::replySet, this, &MainWindow::parseApiReply);
    //connect rfid reader and start the aplication
    connect(rfid, &Rfid::cardNumber, this, &MainWindow::pinScreen);
    language = 0;
    startScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTimer()
{
    runtime++;
    qDebug()<<"------------------------------------------------------ application runtime:"<<runtime<<"seconds";
    if(appState != 0)
    {
        logoutTimer-=1;
        QString logoutTimerText = QString::number(logoutTimer);
        QString logoutInfoText = "";
        if(language==0)
        {
            logoutInfoText = " seconds to automatic logout";
        }
        if(language==1)
        {
            logoutInfoText = " sekuntia automaattiseen uloskirjautumiseen";
        }
        if(language==2)
        {
            logoutInfoText = " sekunder för automatisk utloggning";
        }
        QString combinedText = logoutTimerText + logoutInfoText;
        ui->logoutInfo->setText(combinedText);
    }
    if(appState != 0 && logoutTimer==0)
    {
        startScreen();
    }
}

void MainWindow::startScreen()
{
    qDebug()<<"startScreen()..";
    appState=0;
    language_startScreen();
    disconnectAllFunctions();
    ui->logoutInfo->setText("");
}

void MainWindow::language_startScreen()
{
    ui->lineEdit->setText(dictionary["Insert card"][language]);
    ui->btnA->setText("");
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}

void MainWindow::pinScreen(QString cNum)
{
    qDebug()<<"pinScreen()..";
    logoutTimer=60;
    appState=1;
    language_pinScreen();
    disconnectAllFunctions();
    serial = cNum;
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::startScreen);
    createPinUI();
}

void MainWindow::language_pinScreen()
{
    ui->lineEdit->setText(dictionary["Insert pin"][language] + ": " + pinAttempts + " " + dictionary["Tries left"][language] );
    ui->btnA->setText(dictionary["Abort transaction"][language]);
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}

void MainWindow::mainScreen()
{
    qDebug()<<"mainScreen()..";
    appState=2;
    withdraw=0;
    withdrawSum=0;
    withdrawInText="";
    language_mainScreen();
    disconnectAllFunctions();
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::startScreen);
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::showBalance);
    connect(ui->btnC, &QPushButton::clicked, this, &MainWindow::showTransactions);
    connect(ui->btnD, &QPushButton::clicked, this, &MainWindow::showWithdraw);
}

void MainWindow::language_mainScreen()
{
    ui->lineEdit->setText(dictionary["Choose action"][language]);
    ui->btnA->setText(dictionary["Abort transaction"][language]);
    ui->btnB->setText(dictionary["Account balance"][language]);
    ui->btnC->setText(dictionary["Account transactions"][language]);
    ui->btnD->setText(dictionary["Withdrawal"][language]);
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}

void MainWindow::showBalance()
{
    qDebug()<<"showBalance()..";
    appState=3;
    language_showBalance();
    disconnectAllFunctions();
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::mainScreen);
    api->getAccountBalance(cu_id);
    apiState = "accountBalance";
}

void MainWindow::language_showBalance()
{
    ui->btnA->setText(dictionary["Back"][language]);
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}


void MainWindow::showTransactions()
{
    qDebug()<<"showTransactions()..";
    appState=4;
    language_showTransactions();
    disconnectAllFunctions();
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::mainScreen);
    connect(ui->btnE, &QPushButton::clicked, this, &MainWindow::showOlder);
    connect(ui->btnF, &QPushButton::clicked, this, &MainWindow::showNewer);
    api->getTransactions(ac_id, start, stop); //TODO: add logic to start and stop
}

void MainWindow::language_showTransactions()
{
    ui->btnA->setText(dictionary["Back"][language]);
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText(dictionary["Show older"][language]);
    ui->btnF->setText(dictionary["Show newer"][language]);
    ui->btnG->setText("");
    ui->btnH->setText("");
}


void MainWindow::showWithdraw()
{
    qDebug()<<"showTransactions()..";
    appState=5;
    language_showWithdraw();
    disconnectAllFunctions();
    setUiTextBalance();
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::mainScreen);
    connect(ui->btnB, &QPushButton::clicked, this, &MainWindow::withdrawConfirmation);
    connect(ui->btnC, &QPushButton::clicked, this, &MainWindow::withdraw20);
    connect(ui->btnD, &QPushButton::clicked, this, &MainWindow::withdraw40);
    connect(ui->btnE, &QPushButton::clicked, this, &MainWindow::withdraw60);
    connect(ui->btnF, &QPushButton::clicked, this, &MainWindow::withdraw90);
    connect(ui->btnG, &QPushButton::clicked, this, &MainWindow::withdraw140);
    connect(ui->btnH, &QPushButton::clicked, this, &MainWindow::withdraw240);
}

void MainWindow::language_showWithdraw()
{
    ui->btnA->setText(dictionary["Back"][language]);
    ui->btnB->setText("Confirm");
    ui->btnC->setText("20€");
    ui->btnD->setText("40€");
    ui->btnE->setText("60€");
    ui->btnF->setText("90€");
    ui->btnG->setText("140€");
    ui->btnH->setText("240€");
}

void MainWindow::withdrawConfirmation()
{
    qDebug()<<"withdrawConfirmation()..";
    appState=6;
    language_withdrawConfirmation();
    withdrawSum = withdraw;
    disconnectAllFunctions();
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::mainScreen);
    connect(ui->btnE, &QPushButton::clicked, this, &MainWindow::withdrawAmount);
    QString rivi1 = "Withdrawing: ";
    QString rivi2 = "€";
    QString combinedText = rivi1 + withdrawInText + rivi2;
    ui->lineEdit->setText(combinedText);
}

void MainWindow::language_withdrawConfirmation()
{
    ui->btnA->setText(dictionary["Back"][language]);
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("Confirm");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
}

void MainWindow::withdrawAmount()
{
    qDebug()<<withdrawSum<<"€ nostettu";
    withdraw=0;
    withdrawSum=0;
    withdrawInText="";
    createKuitti();
    startScreen();
}

void MainWindow::parseApiReply(QString lastReply)
{
    if(apiState == "login"){
        if(lastReply != "false"){
            api->token = lastReply;
            api->getAccountId(serial);
            apiState = "accountId";
        }
        else{
            qDebug() << "Wrong password!";
        }
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
            ui->lineEdit->setText(dictionary["Account balance"][language] + balance);

        }
        else if(type == "credit"){
            ui->lineEdit->setText(dictionary["Account balance"][language] + credit);
        }
    }
    else if(apiState == "transactions"){
        ui->lineEdit->setText(dictionary["Account transactions"][language] + "\n");
        QString oldText;
        auto result = lastReply.split(", ");
        if(lastReply.isEmpty()){
            transactionStopper = true;
        }
        else{
            transactionStopper = false;
        }

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
    qDebug()<<"Syötetty PIN: "<<tryPin;
    logoutTimer=60;
    pin = tryPin;
    apiState = "login";
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

void MainWindow::showOlder()
{
    if(!transactionStopper){
        start += 5;
        stop += 5;
    }


}

void MainWindow::showNewer()
{
    if (start > 0 && stop > 5){
        start -= 5;
        stop -= 5;
    }


}

void MainWindow::createPinUI()
{
    PinUI* PinWindow = new PinUI;
    connect(PinWindow, SIGNAL(sendPin(QString)), this, SLOT(checkPassword(QString)));
    PinWindow->show();
}

void MainWindow::createKuitti()
{
    printtaus.play();
    Kuitti* KuittiWindow = new Kuitti;
    KuittiWindow->show();
}
void MainWindow::createRfid() {
    Rfid* RfidWindow = new Rfid;
    RfidWindow->show();
}


void MainWindow::on_RFIDButton_clicked()
{
    qDebug()<<"*kortti 0000411932 syötetty koneeseen..";
    RFIDpressed = true;
    pinScreen("0000411932");
}

void MainWindow::on_PINButton_clicked()
{
    appState=2;
    mainScreen();
}


void MainWindow::on_KuittiButton_clicked()
{
    qDebug()<<"tulostetaan tyhjä kuitti..";
}

void MainWindow::on_btnA_clicked()
{
    qDebug()<<"A-toimintoa painettu..";
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnB_clicked()
{
    qDebug()<<"B-toimintoa painettu..";
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnC_clicked()
{
    qDebug()<<"C-toimintoa painettu..";
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnD_clicked()
{
    qDebug()<<"D-toimintoa painettu..";
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnE_clicked()
{
    qDebug()<<"E-toimintoa painettu..";
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnF_clicked()
{
    qDebug()<<"F-toimintoa painettu..";
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnG_clicked()
{
    qDebug()<<"G-toimintoa painettu..";
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnH_clicked()
{
    qDebug()<<"H-toimintoa painettu..";
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_english_clicked()
{
    beep.play();
    logoutTimer=60;
    language = 0;
    switch (appState) {
    case 0:
        language_startScreen();
        break;
    case 1:
        language_pinScreen();
        break;
    case 2:
        language_mainScreen();
        break;
    case 3:
        language_showBalance();
        break;
    case 4:
        language_showTransactions();
        break;
    case 5:
        language_showWithdraw();
        break;
    case 6:
        language_withdrawConfirmation();
        break;
    default:
        break;
    }
}


void MainWindow::on_finnish_clicked()
{
    beep.play();
    logoutTimer=60;
    language = 1;
    switch (appState) {
    case 0:
        language_startScreen();
        break;
    case 1:
        language_pinScreen();
        break;
    case 2:
        language_mainScreen();
        break;
    case 3:
        language_showBalance();
        break;
    case 4:
        language_showTransactions();
        break;
    case 5:
        language_showWithdraw();
        break;
    case 6:
        language_withdrawConfirmation();
        break;
    default:
        break;
    }
}


void MainWindow::on_swedish_clicked()
{
    beep.play();
    logoutTimer=60;
    language = 2;
    switch (appState) {
    case 0:
        language_startScreen();
        break;
    case 1:
        language_pinScreen();
        break;
    case 2:
        language_mainScreen();
        break;
    case 3:
        language_showBalance();
        break;
    case 4:
        language_showTransactions();
        break;
    case 5:
        language_showWithdraw();
        break;
    case 6:
        language_withdrawConfirmation();
        break;
    default:
        break;
    }
}

void MainWindow::setUiTextBalance()
{
    qDebug()<<"setUiTextBalance()..";
    withdrawInText = QString::number(withdraw);
    QString chooseSum1 = "";
    if(language==0)
    {
         chooseSum1 = "Choose sum: ";
    }
    if(language==1)
    {
        chooseSum1 = "Valitse summa: ";
    }
    if(language==2)
    {
        chooseSum1 = "Välj summa: ";
    }
    QString chooseSum2 = "€";
    QString combinedText = chooseSum1 + withdrawInText + chooseSum2;
    ui->lineEdit->setText(combinedText);
}

void MainWindow::withdraw20()
{
    if(withdraw<381)
    {
        withdraw+=20;
        setUiTextBalance();
    }
}

void MainWindow::withdraw40()
{
    if(withdraw<361)
    {
        withdraw+=40;
        setUiTextBalance();
    }
}
void MainWindow::withdraw60()
{
    if(withdraw<341)
    {
        withdraw+=60;
        setUiTextBalance();
    }
}

void MainWindow::withdraw90()
{
    if(withdraw<311)
    {
        withdraw+=90;
        setUiTextBalance();
    }
}

void MainWindow::withdraw140()
{
    if(withdraw<261)
    {
        withdraw+=140;
        setUiTextBalance();
    }
}

void MainWindow::withdraw240()
{
    if(withdraw<161)
    {
        withdraw+=240;
        setUiTextBalance();
    }
}

void MainWindow::disconnectAllFunctions()
{
    disconnect(ui->btnA, &QPushButton::clicked, this, &MainWindow::startScreen);
    disconnect(ui->btnA, &QPushButton::clicked, this, &MainWindow::mainScreen);

    disconnect(ui->btnB, &QPushButton::clicked, this, &MainWindow::showBalance);
    disconnect(ui->btnB, &QPushButton::clicked, this, &MainWindow::withdrawConfirmation);

    disconnect(ui->btnC, &QPushButton::clicked, this, &MainWindow::showTransactions);
    disconnect(ui->btnC, &QPushButton::clicked, this, &MainWindow::withdraw20);

    disconnect(ui->btnD, &QPushButton::clicked, this, &MainWindow::showWithdraw);
    disconnect(ui->btnD, &QPushButton::clicked, this, &MainWindow::withdraw40);

    disconnect(ui->btnE, &QPushButton::clicked, this, &MainWindow::showOlder);
    disconnect(ui->btnE, &QPushButton::clicked, this, &MainWindow::withdraw60);

    disconnect(ui->btnF, &QPushButton::clicked, this, &MainWindow::showNewer);
    disconnect(ui->btnF, &QPushButton::clicked, this, &MainWindow::withdraw90);

    disconnect(ui->btnG, &QPushButton::clicked, this, &MainWindow::withdraw140);

    disconnect(ui->btnH, &QPushButton::clicked, this, &MainWindow::withdraw240);

    disconnect(ui->btnE, &QPushButton::clicked, this, &MainWindow::withdrawAmount);
}
