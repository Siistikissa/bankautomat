#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qpushbutton.h"
#include "rfid_dll.h"
#include <QMainWindow>
#include <Qstring>
#include <QLineEdit>
#include <QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void createObject();
    void readRfidData();
private:
    Ui::MainWindow *ui;
    QPushButton *m_button;
    QSerialPort *PORT;
    QLineEdit *m_lineEdit;
    Rfid_dll *m_rfidObject;
};
#endif // MAINWINDOW_H
