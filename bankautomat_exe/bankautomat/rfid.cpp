#include "rfid.h"

Rfid::Rfid()
{
    if(!QSerialPortInfo::availablePorts().isEmpty()){                               //If serial port have not been connected yet
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts())    //Loop trought all ports
    {
    PORT = new QSerialPort();                                                       //Create object for each port found
    PORT->setPortName(portInfo.portName());                                         //Sets portname to correct com
    PORT->open(QIODevice::ReadWrite);                                               //Opens the serialport for read and write
    }
    connect(PORT, PORT->readyRead(), this, Rfid::readRfidData);                       //connect read data when data is readed
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
    QByteArray data = PORT->readAll();                      //Reads all data from object to data array
    QString rfidData = (data);                              //Convert it to string
    rfidData.remove('-');                                   //Remove all extra characters
    rfidData.remove('>');
    rfidData.remove(QRegularExpression("[^0-9]"));
    qDebug() <<"rfid " <<rfidData;
    emit cardNumber(rfidData);                              //Send data in signal to mainwindow
}
