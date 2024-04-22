#ifndef RFID_H
#define RFID_H

#include "qpushbutton.h"
#include <QObject>
#include <QSerialPort>
#include <Qstring>
#include <QSerialPortInfo>
#include <QRegularExpression>

class Rfid : public QWidget
{
    Q_OBJECT

public:
    Rfid();
    ~Rfid();
signals:
    void cardNumber(QString cNum);
private slots:
    void openSerialPort();
    void readRfidData();

private:
    QPushButton *m_button;
    QSerialPort *PORT;
};
#endif // RFID_H
