#include "kuitti.h"
#include "ui_kuitti.h"
#include <QLabel>
#include <QPixmap>
#include <QPainter>

Kuitti::Kuitti(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kuitti)
{
        ui->setupUi(this);

    QPixmap image("C://Users//sanin//OneDrive//Kuvat//ripped_receipt_1.png");

    QImage img(image.size(), QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::transparent);
    QPainter painter(&img);
    painter.drawPixmap(0, 0, image);

    QFont originalFont = painter.font();

    QRect textRect1(10, 20, img.width() - 20, 20);
    painter.setPen(Qt::black);
    painter.drawText(textRect1, Qt::AlignJustify | Qt::AlignTop, "-----------------------------------------------------------------------");

    QFont font = painter.font();
    font.setPointSize(12);
    font.setBold(true);
    painter.setFont(font);

    QRect textRect2(10, 40, img.width() - 20, 20);
    painter.drawText(textRect2, Qt::AlignHCenter | Qt::AlignTop, "PANKKIAUTOMAATTI");

    painter.setFont(originalFont);

    QRect textRect3(10, 60, img.width() - 20, 20);
    painter.drawText(textRect3, Qt::AlignJustify | Qt::AlignTop, "----------------------------------------------------------------------");

    QRect textRect4(10, 90, img.width() - 20, 20);
    painter.drawText(textRect4, Qt::AlignLeft | Qt::AlignTop, "ATM NUMBER: 80085");

    QRect textRect5(10, 120, img.width() - 20, 20);
    painter.drawText(textRect5, Qt::AlignLeft | Qt::AlignTop, "VESA");

    QRect textRect6(10, 120, img.width() - 20, 20);
    painter.drawText(textRect6, Qt::AlignRight | Qt::AlignTop, "DEBIT VAI CREDIT");

    QRect textRect7(10, 150, img.width() - 20, 20);
    painter.drawText(textRect7, Qt::AlignLeft | Qt::AlignTop, "CUSTOMER:");

    QRect textRect8(10, 150, img.width() - 20, 20);
    painter.drawText(textRect8, Qt::AlignRight | Qt::AlignTop, "NIMI SUKUNIMI");

    QRect textRect9(10, 210, img.width() - 20, 20);
    painter.drawText(textRect9, Qt::AlignLeft | Qt::AlignTop, "TRANSACTION:");

    QRect textRect10(10, 240, img.width() - 20, 20);
    painter.drawText(textRect10, Qt::AlignRight | Qt::AlignTop, "XXXXXXXXX");

    QRect textRect19(10, img.height() - 80, img.width() - 20, 20);
    painter.drawText(textRect19, Qt::AlignLeft | Qt::AlignBottom, "---------------------------------------------------------------------");

    QRect textRect20(10, img.height() - 60, img.width() - 20, 20);
    painter.drawText(textRect20, Qt::AlignLeft | Qt::AlignBottom, "TOTAL:");

    QRect textRect21(10, img.height() - 60, img.width() - 20, 20);
    painter.drawText(textRect21, Qt::AlignRight | Qt::AlignBottom, "XXXXXXXX");


    painter.end();
    
    QDir directory("../bankautomat/");
    QString pathToPrint = directory.absoluteFilePath("printtaus.wav");
    printtaus.setSource(QUrl::fromLocalFile(pathToPrint));
    printtaus.setVolume(1.0);
    printtaus.play();

    qDebug() << "Ikkunan koko:" << this->size();
}

Kuitti::~Kuitti()
{
    delete ui;
}
