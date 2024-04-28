#include "kuitti.h"
#include "ui_kuitti.h"
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QVBoxLayout>

Kuitti::Kuitti(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Kuitti)
{

}

Kuitti::~Kuitti()
{
    delete ui;
}

void Kuitti::setParameters(QString serial, QString type, int transaction, std::vector<QString> transactionsVector)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout;
    
    QDir directory("../");
    QPixmap image = directory.absoluteFilePath("ripped_receipt_1.png");
  
    QImage img(image.size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    QPainter painter(&img);
    painter.drawPixmap(0, 0, image);

    QFont originalFont = painter.font();

    QRect textRect1(10, 70, img.width() - 20, 20);
    painter.setPen(Qt::black);
    painter.drawText(textRect1, Qt::AlignJustify | Qt::AlignTop, "-----------------------------------------------------------------------");

    QFont font = painter.font();
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    QRect textRect2(10, 90, img.width() - 20, 20);
    painter.drawText(textRect2, Qt::AlignHCenter | Qt::AlignTop, "PANKKIAUTOMAATTI");

    painter.setFont(originalFont);

    QRect textRect3(10, 110, img.width() - 20, 20);
    painter.drawText(textRect3, Qt::AlignJustify | Qt::AlignTop, "----------------------------------------------------------------------");

    QRect textRect4(10, 130, img.width() - 20, 20);
    painter.drawText(textRect4, Qt::AlignHCenter | Qt::AlignTop, "PARATIISITIE 13");

    QRect textRect45(10, 150, img.width() - 20, 20);
    painter.drawText(textRect45, Qt::AlignHCenter | Qt::AlignTop, "99999, ANKKALINNA");

    QRect textRect5(10, 170, img.width() - 20, 20);
    painter.drawText(textRect5, Qt::AlignHCenter | Qt::AlignTop, "ATM NUMBER: 80085");

    QRect textRect6(10, 205, img.width() - 20, 20);
    painter.drawText(textRect6, Qt::AlignLeft | Qt::AlignTop, "DATE:");

    QDate date = QDate::currentDate();
    QString dateString = date.toString("dd.MM.yyyy");

    QRect textRect7(10, 220, img.width() - 20, 20);
    painter.drawText(textRect7, Qt::AlignLeft | Qt::AlignTop, dateString);

    QRect textRect8(90, 205, img.width() - 20, 20);
    painter.drawText(textRect8, Qt::AlignLeft | Qt::AlignTop, "CLOCK:");

    QTime currentTime = QTime::currentTime();
    QString currentTimeString = currentTime.toString("hh:mm:ss");

    QRect textRect9(90, 220, img.width() - 20, 20);
    painter.drawText(textRect9, Qt::AlignLeft | Qt::AlignTop, currentTimeString);

    QRect textRect10(160, 205, img.width() - 20, 20);
    painter.drawText(textRect10, Qt::AlignLeft | Qt::AlignTop, "REFERENCE:");

    QString reference;
    for (int i = 0; i < 4; ++i)
    {
        int randomNumber = rand() % 10;
        reference += QString::number(randomNumber);
    }

    QRect textRect11(160, 220, img.width() - 20, 20);
    painter.drawText(textRect11, Qt::AlignLeft | Qt::AlignTop, reference);

    QRect textRect12(10, 250, img.width() - 20, 20);
    painter.drawText(textRect12, Qt::AlignLeft | Qt::AlignTop, "VISA");

    QRect textRect120(135, 250, img.width() - 20, 20);
    painter.drawText(textRect120, Qt::AlignLeft | Qt::AlignTop, ":");

    QRect textRect13(150, 250, img.width() - 20, 20);
    painter.drawText(textRect13, Qt::AlignLeft | Qt::AlignTop, type);

    QRect textRect14(10, 265, img.width() - 20, 20);
    painter.drawText(textRect14, Qt::AlignLeft | Qt::AlignTop, "CARD NUMBER");

    QRect textRect140(135, 265, img.width() - 20, 20);
    painter.drawText(textRect140, Qt::AlignLeft | Qt::AlignTop, ":");

    serial.replace(0, 5, "XXXXX");

    QRect textRect15(150, 265, img.width() - 20, 20);
    painter.drawText(textRect15, Qt::AlignLeft | Qt::AlignTop, serial);

    QRect textRect16(10, 280, img.width() - 20, 20);
    painter.drawText(textRect16, Qt::AlignLeft | Qt::AlignTop, "REFERENCE NUMBER");

    QRect textRect160(135, 280, img.width() - 20, 20);
    painter.drawText(textRect160, Qt::AlignLeft | Qt::AlignTop, ":");

    QString referenceNumber;
    for (int i = 0; i < 12; ++i)
    {
        int randomNumber = rand() % 10;
        referenceNumber += QString::number(randomNumber);
    }

    QRect textRect17(150, 280, img.width() - 20, 20);
    painter.drawText(textRect17, Qt::AlignLeft | Qt::AlignTop, referenceNumber);

    QFont font1;
    font1.setPointSize(12);
    font1.setBold(true);
    painter.setFont(font1);

    QRect textRect18(10, 300, img.width() - 20, 20);
    painter.drawText(textRect18, Qt::AlignHCenter | Qt::AlignTop, "WITHDRAWAL");

    painter.setFont(originalFont);

    QRect textRect19(10, 330, img.width() - 20, 20);
    painter.drawText(textRect19, Qt::AlignLeft | Qt::AlignTop, "AMOUNT");

    QRect textRect20(10, 330, img.width() - 20, 20);
    painter.drawText(textRect20, Qt::AlignRight | Qt::AlignTop, QString::number(transaction));

    QFont boldFont;
    boldFont.setPointSize(12);
    boldFont.setBold(true);

    QRect textRect21(10, img.height() - 80, img.width() - 20, 20);
    painter.setFont(boldFont);
    painter.drawText(textRect21, Qt::AlignHCenter | Qt::AlignBottom, "THANK YOU FOR STOPPING BY");

    QRect textRect22(10, img.height() - 50, img.width() - 20, 20);
    painter.drawText(textRect22, Qt::AlignHCenter | Qt::AlignBottom, "WELCOME AGAIN!");

    painter.end();

    QLabel *label = new QLabel(this);
    label->setPixmap(QPixmap::fromImage(img));
    layout->addWidget(label);
    setLayout(layout);
}

