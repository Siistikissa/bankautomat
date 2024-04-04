#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "pinui.h"
#include <QMainWindow>
#include <QDebug>

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

private slots:
    void on_RFIDButton_clicked();
    void on_PINUIButton_clicked();

private:
    Ui::MainWindow *ui;
    void createBankUI();
    bool RFIDpressed = false;
};
#endif // MAINWINDOW_H
