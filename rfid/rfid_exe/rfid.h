#ifndef RFIDTEST_H
#define RFIDTEST_H

#include <QMainWindow>
#include "qpushbutton.h"
#include "rfid_dll.h"
#include <QSerialPort>
#include <Qstring>
#include <QLineEdit>

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
    void OpenSerialPort();
    void readRfidData();
private:
    Ui::MainWindow *ui;
    QPushButton *m_button;
    QSerialPort *PORT;
    QLineEdit *m_lineEdit;
};
#endif // RFIDTEST_H
