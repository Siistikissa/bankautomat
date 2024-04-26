#include "rfid.h"

Rfid::Rfid()
{
    if(!QSerialPortInfo::availablePorts().isEmpty()){
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts())
    {
    PORT = new QSerialPort();
    PORT->setPortName(portInfo.portName());
    PORT->open(QIODevice::ReadWrite);
    }
    connect(PORT, PORT->readyRead, this, Rfid::readRfidData);
    }
    else{
        qDebug() << "Cardreader not found!";
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
    qDebug() <<"rfid " <<rfidData;
    emit cardNumber(rfidData);
}
