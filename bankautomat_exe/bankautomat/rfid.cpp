#include "rfid.h"

Rfid::Rfid()
{
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts())
    {
    PORT = new QSerialPort();
    PORT->setPortName(portInfo.portName());
    PORT->open(QIODevice::ReadWrite);
    }
    //will not work is cardreader is not connected
    try{
    connect(PORT, &QSerialPort::readyRead, this, &Rfid::readRfidData);

    }
    catch(...){
        qDebug() << "HELP HELP HELP!!!!!!!!!";
    };
   /* try{
    if (PORT->isOpen()){

    } else {

        throw 2000;
    }

    }
    catch(...){
        qDebug() << "Card reader not connected.";
    };
*/
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
