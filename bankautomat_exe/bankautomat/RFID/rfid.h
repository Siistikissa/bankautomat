#ifndef RFID_H
#define RFID_H

#include <QWidget>
#include <QSerialPort>
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
    QSerialPort *PORT;
};

#endif // RFID_H
