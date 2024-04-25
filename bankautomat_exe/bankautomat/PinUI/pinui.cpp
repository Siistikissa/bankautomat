#include "pinui.h"
#include "ui_pinui.h"

using namespace std;

PinUI::PinUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinUI)
{
    qDebug()<<"pinui buildattu oikein?";
    beep.setSource(QUrl::fromLocalFile("C:\\projektit\\pankkiautomaatti\\SPL_Group8\\bankautomat_exe\\bankautomat\\beep.wav"));
    beep.setVolume(1.0);
    lowbeep.setSource(QUrl::fromLocalFile("C:\\projektit\\pankkiautomaatti\\SPL_Group8\\bankautomat_exe\\bankautomat\\lowbeep.wav"));
    lowbeep.setVolume(1.0);
    ui->setupUi(this);
}

PinUI::~PinUI()
{
    delete ui;
}

void PinUI::on_pushButton_clicked()
{
    beep.play();
    close();
}

void PinUI::on_btnEnter_clicked()
{
    if(state>=5)
    {
        beep.play();
        ui->lineEdit->setText(input);
        emit sendPin(input);
    }
    else
    {
        lowbeep.play();
        ui->lineEdit->setText("Invalid PIN");
    }
}

void PinUI::on_btnClear_clicked()
{   
    beep.play();
    input.clear();
    state=1;
    ui->lineEdit->setText("");
}

void PinUI::on_btn0_clicked()
{
    buttonInput('0');
}

void PinUI::on_btn1_clicked()
{
    buttonInput('1');
}

void PinUI::on_btn2_clicked()
{
    buttonInput('2');
}

void PinUI::on_btn3_clicked()
{
    buttonInput('3');
}

void PinUI::on_btn4_clicked()
{
    buttonInput('4');
}

void PinUI::on_btn5_clicked()
{
    buttonInput('5');
}

void PinUI::on_btn6_clicked()
{
    buttonInput('6');
}

void PinUI::on_btn7_clicked()
{
    buttonInput('7');
}

void PinUI::on_btn8_clicked()
{ 
    buttonInput('8');
}

void PinUI::on_btn9_clicked()
{
    buttonInput('9');
}

void PinUI::buttonInput(char buttonNum)
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        if(state==1)
        {
            input+=buttonNum;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=buttonNum;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=buttonNum;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=buttonNum;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}
