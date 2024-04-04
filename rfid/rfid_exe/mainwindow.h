#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qpushbutton.h"
#include "rfid_dll.h"
#include <QString>
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
public slots:
    void onRfidDataReceived(QByteArray data);
private slots:
    void OpenSerialPort();
private:
    Ui::MainWindow *ui;
    Rfid_dll *rfidDll=new Rfid_dll;
    QPushButton *m_button;
    QLineEdit *m_lineEdit;

};
#endif // MAINWINDOW_H
