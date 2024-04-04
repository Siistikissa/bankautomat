#include "rfid_dll.h"

Rfid_dll::Rfid_dll()
{
    PORT = new QSerialPort();
    PORT->setPortName("COM5");
    PORT->open(QIODevice::ReadWrite);
    if (PORT->isOpen()){
        qDebug()<<"Port is open";
        QSerialPort::connect(PORT, &QSerialPort::readyRead, this, &Rfid_dll::onReadyRead);
    }else{
        qDebug()<<"Port failed to open";
    }
}

void Rfid_dll::onReadyRead() {
    rfid = PORT->readAll();

}
