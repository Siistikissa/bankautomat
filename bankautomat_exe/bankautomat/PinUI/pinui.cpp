#include "pinui.h"
#include "ui_pinui.h"

using namespace std;

PinUI::PinUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PinUI)
{
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
        QString inputQ = QString::fromStdString(input);
        emit sendPin(inputQ);
        close();
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
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='0';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
         input+=num;
          ui->lineEdit->setText("**");
       }
       if(state==3)
       {
           input+=num;
           ui->lineEdit->setText("***");
       }
       if(state==4)
       {
           input+=num;
           ui->lineEdit->setText("****");
       }
       state++;
    }
}

void PinUI::on_btn1_clicked()
{
    if(state>=5)
    {
       lowbeep.play();
    }
    else
    {
        beep.play();
        char num='1';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}

void PinUI::on_btn2_clicked()
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='2';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
        input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}

void PinUI::on_btn3_clicked()
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='3';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}

void PinUI::on_btn4_clicked()
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='4';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}

void PinUI::on_btn5_clicked()
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='5';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}

void PinUI::on_btn6_clicked()
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='6';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}

void PinUI::on_btn7_clicked()
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='7';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}

void PinUI::on_btn8_clicked()
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='8';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}

void PinUI::on_btn9_clicked()
{
    if(state>=5)
    {
        lowbeep.play();
    }
    else
    {
        beep.play();
        char num='9';
        if(state==1)
        {
            input+=num;
            ui->lineEdit->setText("*");
        }
        if(state==2)
        {
            input+=num;
            ui->lineEdit->setText("**");
        }
        if(state==3)
        {
            input+=num;
            ui->lineEdit->setText("***");
        }
        if(state==4)
        {
            input+=num;
            ui->lineEdit->setText("****");
        }
        state++;
    }
}
