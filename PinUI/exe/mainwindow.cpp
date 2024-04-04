#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::createPinUI);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createPinUI()
{
    PinUI* PinWindow = new PinUI;
    PinWindow->show();
}


void MainWindow::on_pushButton_clicked()
{

}
