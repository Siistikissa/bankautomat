#include "pinui.h"
#include "ui_pinui.h"

using namespace std;

PinUI::PinUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinUI)
{
    beep.setSource(QUrl::fromLocalFile("C:\\projektit\\testiohjelma\\PinUI\\beep.wav"));
    beep.setVolume(1.0); // Adjust the volume as needed
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

void PinUI::on_btn0_clicked()
{
    beep.play();
    char num='0';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn1_clicked()
{
    beep.play();
    char num='1';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn2_clicked()
{
    beep.play();
    char num='2';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn3_clicked()
{
    beep.play();
    char num='3';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn4_clicked()
{
    beep.play();
    char num='4';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn5_clicked()
{
    beep.play();
    char num='5';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn6_clicked()
{
    beep.play();
    char num='6';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn7_clicked()
{
    beep.play();
    char num='7';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn8_clicked()
{
    beep.play();
    char num='8';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}

void PinUI::on_btn9_clicked()
{
    beep.play();
    char num='9';
    if(state==0)
    {
        input+=num;
        ui->lineEdit->setText("*");
    }
    if(state==1)
    {
        input+=num;
        ui->lineEdit->setText("**");
    }
    if(state==2)
    {
        input+=num;
        ui->lineEdit->setText("***");
    }
    if(state==3)
    {
        input+=num;
        ui->lineEdit->setText("****");
    }
    state++;
}
