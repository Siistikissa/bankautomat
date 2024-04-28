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
    //setup paths to sounds and images
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
    appState=0;
    language_startScreen();
    disconnectAllFunctions();
    ui->logoutInfo->setText("");
}

void MainWindow::language_startScreen()
{
    ui->textEdit->setText(dictionary["Insert card"][language]);
    ui->btnA->setText("");
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::pinScreen(QString cNum)
{
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
    ui->textEdit->setText(dictionary["Wrong pin"][language]);
    ui->btnA->setText(dictionary["Abort transaction"][language]);
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::mainScreen()
{
    appState=2;
    withdraw=0;
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
    ui->textEdit->setText(dictionary["Choose action"][language]);
    ui->btnA->setText(dictionary["Abort transaction"][language]);
    ui->btnB->setText(dictionary["Account balance"][language]);
    ui->btnC->setText(dictionary["Account transactions"][language]);
    ui->btnD->setText(dictionary["Withdrawal"][language]);
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::showBalance()
{
    appState=3;
    disconnectAllFunctions();
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::mainScreen);
    //apiState = "accountBalance";
    //api->getAccountBalance(cu_id);
    language_showBalance();
}

void MainWindow::language_showBalance()
{
    ui->btnA->setText(dictionary["Back"][language]);
    ui->btnB->setText("");
            if(type == "balance"){
            ui->textEdit->setText(dictionary["Account balance"][language] + " " + QString::number(balance) + "€");

        }
        else if(type == "credit"){
            ui->textEdit->setText(dictionary["Account balance"][language] + " " + QString::number(credit) + "€");
        }
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText("");
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}


void MainWindow::showTransactions()
{
    appState=4;
    language_showTransactions();
    disconnectAllFunctions();
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::mainScreen);
    connect(ui->btnE, &QPushButton::clicked, this, &MainWindow::showOlder);
    connect(ui->btnF, &QPushButton::clicked, this, &MainWindow::showNewer);
    apiState = "transactions";
    api->getTransactions(ac_id, start, stop);
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
    ui->textEdit->setAlignment(Qt::AlignCenter);
}


void MainWindow::showWithdraw()
{
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
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::withdrawConfirmation()
{
    appState=6;
    language_withdrawConfirmation();
    if(checkWithdraw()){
        apiState = "withdraw";
    api->postWithdraw(type, newAmount, cu_id, transaction, ac_id);
    disconnectAllFunctions();
    connect(ui->btnA, &QPushButton::clicked, this, &MainWindow::mainScreen);
    connect(ui->btnE, &QPushButton::clicked, this, &MainWindow::withdrawAmount);
    QString rivi1 = "Withdrawing: ";
    QString rivi2 = "€";
    QString combinedText = rivi1 + withdrawInText + rivi2;
    ui->textEdit->setText(combinedText);
    }
    else{
        ui->textEdit->setText(dictionary["Insufficient funds"][language]);//add insuffienct credit
        ui->btnE->setText("");
        disconnect(ui->btnE, &QPushButton::clicked, this, &MainWindow::withdrawConfirmation);
    }
}


void MainWindow::language_withdrawConfirmation()
{
    ui->btnA->setText(dictionary["Back"][language]);
    ui->btnB->setText("");
    ui->btnC->setText("");
    ui->btnD->setText("");
    ui->btnE->setText(dictionary["Confirm"][language]);
    ui->btnF->setText("");
    ui->btnG->setText("");
    ui->btnH->setText("");
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::withdrawAmount()
{
    withdraw=0;
    withdrawInText="";
    createKuitti();
    startScreen();
}

void MainWindow::parseApiReply(QString lastReply)
{
    if(apiState == "login"){
        qDebug() << "login";
        if(lastReply != "false"){
            qDebug() << "send next api cmd " << serial;
            api->token = lastReply;
            apiState = "customerId";
            api->getCustomerId(serial);
        }
        else{
            qDebug() << "Wrong password!";
        }
    }
    else if(apiState == "customerId"){
        cu_id = lastReply.toInt();
        apiState = "accountId";
        qDebug() << cu_id;
        api->getAccountId(cu_id);
    }
    else if(apiState == "accountId"){
        ac_id = lastReply.toInt();
        apiState = "accountBalance";
        api->getAccountBalance(cu_id);
    }
    else if(apiState == "accountBalance"){
        //parse lastreply to 3
        auto result = lastReply.split(", ");
        balance = result[0].toDouble();
        credit = result[1].toDouble();
        if(credit == 0){
            type = "balance";
        }
        else{
            type = "credit";
        }
        apiState= "nothing";
        mainScreen();
    }
    else if (apiState == "transactions") {
        ui->textEdit->setText(dictionary["Account transactions"][language] + "\n");
        QString displayText;

        QStringList result = lastReply.split(", ");
        if (lastReply.isEmpty()) {
            transactionStopper = true;
            if (transactionsVector.size() <= 5){
                for (int x = 0; x < transactionsVector.size(); ++x){
                   ui->textEdit->append(transactionsVector[x]);
                }
            }
            else{
                for (int x = 0; x < 5; ++x){
                    ui->textEdit->append(transactionsVector[x]);
                }
            }
            return;
        } else {
            transactionStopper = false;
        }

        for (int i = 0; i < result.length() / 2; ++i) {
            QString timestamp = QDateTime::fromString(result[result.length() / 2 + i], Qt::ISODate).toString("yyyy-MM-dd, hh:mm:ss");
            QString transactionEntry = result[i] + " €, " + timestamp;

            displayText = transactionEntry; //+ "\n";
            ui->textEdit->append(displayText);

            transactionsVector.push_back(transactionEntry);
            qDebug() << "Transaction entry " << i << ": " << transactionEntry;
        }

    }


}

void MainWindow::checkPassword(QString tryPin)
{
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
    transactionsVector.clear();
    credit = 0;
    balance = 0;
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

    showTransactions();

}

void MainWindow::showNewer()
{
    if (start > 0 && stop > 5){
        start -= 5;
        stop -= 5;
    }

    showTransactions();

}

bool MainWindow::checkWithdraw()
{
    if(type == "balance"){
        if(balance > withdraw){
            transaction = withdraw;
            newAmount = balance-withdraw;
            return true;
        }
    }
    else if(type == "credit"){
        if(credit > withdraw){
            transaction = withdraw;
            newAmount = credit-withdraw;
            return true;
        }
    }
    return false;
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
    KuittiWindow -> setParameters(serial, type, transaction, transactionsVector);
    KuittiWindow->show();
}

void MainWindow::createRfid() {
    Rfid* RfidWindow = new Rfid;
    RfidWindow->show();
}


void MainWindow::on_RFIDButton_clicked()
{
    pinScreen("060006491");

}

void MainWindow::on_btnA_clicked()
{
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnB_clicked()
{
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnC_clicked()
{
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnD_clicked()
{
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnE_clicked()
{
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnF_clicked()
{
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnG_clicked()
{
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_btnH_clicked()
{
    beep.play();
    logoutTimer=60;
}

void MainWindow::on_english_clicked()
{
    beep.play();
    logoutTimer=60;
    language = 0;
    uiRefresh();
}


void MainWindow::on_finnish_clicked()
{
    beep.play();
    logoutTimer=60;
    language = 1;
    uiRefresh();
}


void MainWindow::on_swedish_clicked()
{
    beep.play();
    logoutTimer=60;
    language = 2;
    uiRefresh();
}

void MainWindow::uiRefresh()
{
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

void MainWindow::centralizeText()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextBlockFormat textBlockFormat = cursor.blockFormat();
    textBlockFormat.setAlignment(Qt::AlignCenter);
    cursor.mergeBlockFormat(textBlockFormat);
    ui->textEdit->setTextCursor(cursor);
}

void MainWindow::setUiTextBalance()
{
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
    ui->textEdit->setText(combinedText);
    ui->textEdit->setAlignment(Qt::AlignCenter);

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
