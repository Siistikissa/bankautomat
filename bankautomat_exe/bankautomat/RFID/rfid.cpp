#include "rfid.h"

Rfid::Rfid()
{
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts())
    {
        PORT = new QSerialPort();
        PORT->setPortName(portInfo.portName());
        PORT->open(QIODevice::ReadWrite);
    }
    if (PORT->isOpen()){
        connect(PORT, &QSerialPort::readyRead, this, &Rfid::readRfidData);
    } else {

    }
}

Rfid::~Rfid()
{
    if (PORT && PORT->isOpen()) {
        PORT->close();
    }
    delete PORT;
}

void Rfid::openSerialPort()
{
    this->close();
}
void Rfid::readRfidData()
{
    QByteArray data = PORT->readAll();
    QString rfidData = (data);
    rfidData.remove('-');
    rfidData.remove('>');
    rfidData.remove(QRegularExpression("[^0-9]"));
    emit cardNumber(rfidData);
}
