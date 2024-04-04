#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_button = findChild<QPushButton*>("pushButton");
    if (m_button) {
        connect(m_button, &QPushButton::clicked, this, &MainWindow::OpenSerialPort);
    } else {
        qDebug() << "Failed to find the OpenSerialPort button.";
    }

    m_lineEdit = findChild<QLineEdit*>("lineEdit");
    if (!m_lineEdit) {
        qDebug() << "Failed to find the lineEdit.";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRfidDataReceived(QByteArray data)
{
    QString rfidData(data);
    m_lineEdit->setText(rfidData);
}

void MainWindow::OpenSerialPort()
{
    Rfid_dll Rfid_dll;

}
