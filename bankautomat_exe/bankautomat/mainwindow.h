#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pinui.h"
#include "kuitti.h"
#include "restapi.h"
#include <QMainWindow>
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

private slots:
    void on_RFIDButton_clicked();
    void on_PINUIButton_clicked();
    void on_KuittiButton_clicked();
    void on_btnA_clicked();
    void on_btnB_clicked();
    void on_btnC_clicked();
    void on_btnD_clicked();
    void on_btnE_clicked();
    void on_btnF_clicked();
    void on_btnG_clicked();
    void on_btnH_clicked();

private:
    void vaihe1();
    void vaihe2();
    void vaihe3();
    void naytaTapahtumat();
    void naytaSaldo();
    void nostaRahaa();
    void clearUiButtons();
    void setUiTextBalance(QString lastReply);
    Ui::MainWindow *ui;
    QSoundEffect beep;
    QSoundEffect lowbeep;
    bool RFIDpressed = false;
    Restapi *api = new Restapi;
};
#endif // MAINWINDOW_H
