#include "rfid.h"
#include "ui_rfidtest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_button = findChild<QPushButton*>("pushButton");
    connect(m_button, &QPushButton::clicked, this, &::MainWindow::OpenSerialPort);

    m_lineEdit = findChild<QLineEdit*>("lineEdit");
}

MainWindow::~MainWindow()
{
    if (PORT && PORT->isOpen()) {
        PORT->close();
    }
    delete PORT;
    delete ui;
}

void MainWindow::OpenSerialPort()
{
    PORT = new QSerialPort();
    PORT->setPortName("COM5");
    PORT->open(QIODevice::ReadWrite);

    if (PORT->isOpen()){
        qDebug()<<"Serial Port is open.";
        connect(PORT, &QSerialPort::readyRead, this, &MainWindow::readRfidData);
    } else {
        qDebug() << "Failed to open Serial Port.";
    }

}
void MainWindow::readRfidData()
{
    QByteArray data = PORT->readAll();
    QString rfidData = (data);
    m_lineEdit->setText(rfidData);
}
