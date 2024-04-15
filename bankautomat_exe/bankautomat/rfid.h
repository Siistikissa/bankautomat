#ifndef RFID_H
#define RFID_H

#include <QWidget>
#include "qpushbutton.h"
#include <QSerialPort>
#include <Qstring>
#include <QLineEdit>
#include <QSerialPortInfo>
#include <QRegularExpression>
QT_BEGIN_NAMESPACE
namespace Ui {
class Rfid;
}
QT_END_NAMESPACE

class Rfid : public QWidget
{
    Q_OBJECT

public:
    Rfid(QWidget *parent = nullptr);
    ~Rfid();

private slots:
    void openSerialPort();
    void readRfidData();

private:
    Ui::Rfid *ui;
    QPushButton *m_button;
    QSerialPort *PORT;
    QLineEdit *m_lineEdit;
};
#endif // RFID_H
