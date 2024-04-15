#include "rfid.h"
#include "ui_rfid.h"

Rfid::Rfid(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Rfid)
{
    ui->setupUi(this);

    m_button = findChild<QPushButton*>("pushButton");
    connect(m_button, &QPushButton::clicked, this, &::Rfid::openSerialPort);

    m_lineEdit = findChild<QLineEdit*>("lineEdit");
    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts())
    {
    PORT = new QSerialPort();
    PORT->setPortName(portInfo.portName());
    PORT->open(QIODevice::ReadWrite);
    }
    if (PORT->isOpen()){
        m_lineEdit->setText("Serial Port is open.");
        connect(PORT, &QSerialPort::readyRead, this, &Rfid::readRfidData);
    } else {
        m_lineEdit->setText("Serial Port Failed to open.");
    }
}

Rfid::~Rfid()
{
    if (PORT && PORT->isOpen()) {
        PORT->close();
    }
    delete PORT;
    delete ui;
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
    m_lineEdit->setText(rfidData);
}
