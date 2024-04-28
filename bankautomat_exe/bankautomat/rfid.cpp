#include "rfid.h"

Rfid::Rfid()
{
    if(!QSerialPortInfo::availablePorts().isEmpty()){       //loops trough all ports and creates object for each port
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts())
    {
    PORT = new QSerialPort();
    PORT->setPortName(portInfo.portName()); //sets port name to correct COM
    PORT->open(QIODevice::ReadWrite);   //opens the cerial port for read and write
    }
    connect(PORT, PORT->readyRead, this, Rfid::readRfidData);    //connect read data when data is read
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
void Rfid::readRfidData()   //reads and cleans up the data, sends it as a signal to mainwindow
{
    QByteArray data = PORT->readAll();
    QString rfidData = (data);
    rfidData.remove('-');
    rfidData.remove('>');
    rfidData.remove(QRegularExpression("[^0-9]"));
    qDebug() <<"rfid " <<rfidData;
    emit cardNumber(rfidData);
}
