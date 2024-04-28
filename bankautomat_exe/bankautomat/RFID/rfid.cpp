#include "rfid.h"

Rfid::Rfid()
{
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts()) //loops trough all ports and creates object for each port
    {
        PORT = new QSerialPort();
        PORT->setPortName(portInfo.portName()); //sets port name to correct COM
        PORT->open(QIODevice::ReadWrite); //opens the cerial port for read and write
    }
    if (PORT->isOpen()){
        connect(PORT, &QSerialPort::readyRead, this, &Rfid::readRfidData); //connect read data when data is read
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
void Rfid::readRfidData() //reads and cleans up the data, sends it as a signal to mainwindow
{
    QByteArray data = PORT->readAll();
    QString rfidData = (data);
    rfidData.remove('-');
    rfidData.remove('>');
    rfidData.remove(QRegularExpression("[^0-9]"));
    emit cardNumber(rfidData);
}
