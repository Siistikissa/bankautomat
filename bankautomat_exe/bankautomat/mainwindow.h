#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pinui.h"
#include "kuitti.h"
#include "restapi.h"
#include "rfid.h"
#include <QMainWindow>
#include <QTimer>
#include <QSoundEffect>
#include <QDebug>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void createPinUI();
    void createKuitti();
    void createRfid();
    void checkPassword(QString tryPin);

private slots:
    void updateTimer();
    void on_RFIDButton_clicked();
    void on_btnA_clicked();
    void on_btnB_clicked();
    void on_btnC_clicked();
    void on_btnD_clicked();
    void on_btnE_clicked();
    void on_btnF_clicked();
    void on_btnG_clicked();
    void on_btnH_clicked();
    void on_english_clicked();
    void on_finnish_clicked();
    void on_swedish_clicked();

private:
    void setUiTextBalance();
    void withdraw20();
    void withdraw40();
    void withdraw60();
    void withdraw90();
    void withdraw140();
    void withdraw240();
    void language_startScreen();
    void language_pinScreen();
    void language_mainScreen();
    void language_showBalance();
    void language_showTransactions();
    void language_showWithdraw();
    void withdrawConfirmation();
    void language_withdrawConfirmation();
    void withdrawAmount();
    void disconnectAllFunctions();
    void startScreen();
    void pinScreen(QString cNum);
    void mainScreen();
    void showBalance();
    void showTransactions();
    void showWithdraw();
    void parseApiReply(QString lastReply);
    void clearApiData();
    void showOlder();
    void showNewer();
    bool checkWithdraw();
    void uiRefresh();
    void centralizeText();
    Ui::MainWindow *ui;
    QTimer *timer;
    QSoundEffect beep;
    QSoundEffect lowbeep;
    QSoundEffect printtaus;
    QString withdrawInText;
    QString apiState;
    Restapi *api = new Restapi;
    Rfid *rfid = new Rfid;
    int language; //0-2, 0 = english, 1 = finnish, 2 = swedish
    //values needed for api communcation
    QString serial;
    QString pin;
    QString type;
    std::vector<QString> transactionsVector;
    double credit;
    double balance;
    double withdraw;
    int appState=0;
    int logoutTimer=60;
    int cu_id;
    int ac_id;
    int newAmount;
    int start = 0;
    int stop = 5;
    int transaction;
    bool transactionStopper;
    //dictionary contains multilinquistics
    std::unordered_map<QString, std::vector<QString>> dictionary = {
        {"Insert card",std::vector<QString>() = {"Insert card", "Syötä kortti","Sätt i kortet"}},
        {"Abort transaction",std::vector<QString>() = {"Abort transaction", "Keskytä tapahtuma", "Avbryta transaktionen"}},
        {"Insert pin",std::vector<QString>() = {"Insert pin", "Syötä pin", "Sätt in stift"}},
        {"Account balance",std::vector<QString>() = {"Account balance", "Tilin saldo", "Kontobalans"}},
        {"Account transactions",std::vector<QString>() = {"Account transactions", "Tilin tapahtumat", "Kontotransaktioner"}},
        {"Withdrawal",std::vector<QString>() = {"Withdrawal", "Nosta rahaa", "Uttag"}},
        {"Choose action",std::vector<QString>() = {"Choose action", "Valitse tapahtuma", "Välj åtgärd"}},
        {"Back",std::vector<QString>() = {"Back", "Takaisin", "Tillbaka"}},
        {"Show older",std::vector<QString>() = {"Show older", "Näytä vanhempia", "Visa äldre"}},
        {"Show newer",std::vector<QString>() = {"Show newer", "Näytä uudempia", "Visa nyare"}},
        {"Confirm",std::vector<QString>() = {"Confirm", "Vahvista", "Bekräfta"}},
        {"Wrong pin",std::vector<QString>() = {"Wrong pin", "Väärä pin", "Fel stift"}},
        {"Insufficient funds",std::vector<QString>() = {"Insufficient funds", "Ei riittävästi katetta", "Otillräckliga medel"}},
        {"Choose sum",std::vector<QString>() = {"Choose sum: ", "Valitse summa: ", "Välj summa: "}}
    };
};
#endif // MAINWINDOW_H
