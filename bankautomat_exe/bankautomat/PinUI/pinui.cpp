#include "pinui.h"
#include "ui_pinui.h"

using namespace std;

PinUI::PinUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinUI)
{
    beep.setSource(QUrl::fromLocalFile("C:\\projektit\\pankkiautomaatti\\SPL_Group8\\bankautomat_exe\\bankautomat\\PinUI\\beep.wav"));
    beep.setVolume(1.0);
    ui->setupUi(this);
}

PinUI::~PinUI()
{
    delete ui;
}

void PinUI::on_pushButton_clicked()
{
    close();
}

void PinUI::on_btnEnter_clicked()
{
    if(state>=4)
    {
        ui->lineEdit->setText(QString::fromStdString(input));
    }
    else
    {
        ui->lineEdit->setText("Invalid PIN");
    }
}

void PinUI::on_btnClear_clicked()
{
    input.clear();
    state=0;
    ui->lineEdit->setText("");
}

void PinUI::on_btnDigit_clicked(char num)
{
    beep.play();
    input += num;
    ui->lineEdit->setText(QString("*").repeated(state + 1));
    state++;
}

