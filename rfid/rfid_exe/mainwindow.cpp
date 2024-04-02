#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    m_button = findChild<QPushButton*>("pushButton");
    if (m_button) {
        connect(m_button, &QPushButton::clicked, this, &MainWindow::createObject);
    } else {
        qDebug() << "Failed to find the createObjectButton.";
    }

    m_lineEdit = findChild<QLineEdit*>("lineEdit");
    if (m_lineEdit) {

    } else {
        qDebug() << "Failed to find the lineEdit.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createObject()
{
    m_rfidObject = new Rfid_dll();

    PORT = new QSerialPort();
    PORT->setPortName("COM5");
    PORT->setBaudRate(QSerialPort::BaudRate::Baud9600);
    PORT->setParity(QSerialPort::Parity::NoParity);
    PORT->setDataBits(QSerialPort::DataBits::Data8);
    PORT->setStopBits(QSerialPort::StopBits::OneStop);
    PORT->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
    PORT->open(QIODevice::ReadWrite);

    if (PORT->isOpen()){
        qDebug()<<"Serial Port is open.";
        connect(PORT, &QSerialPort::readyRead, this, &MainWindow::readRfidData);
    }

    else {
        qDebug() << "Failed to open Serial Port.";
    }

}
void MainWindow::readRfidData()
{
    QByteArray data = PORT->readAll(); // Read data from the serial port
    QString rfidData(data); // Convert the QByteArray to QString
    m_lineEdit->setText(rfidData); // Display the data in the QLineEdit widget
}
