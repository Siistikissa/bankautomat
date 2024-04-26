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

    QRect textRect1(10, 25, img.width() - 20, 20);
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
    painter.drawText(textRect4, Qt::AlignHCenter | Qt::AlignTop, "PARATIISITIE 13");

    QRect textRect5(10, 120, img.width() - 20, 20);
    painter.drawText(textRect5, Qt::AlignHCenter | Qt::AlignTop, "ATM NUMBER: 80085");

    QRect textRect6(120, 150, img.width() - 20, 20);
    painter.drawText(textRect6, Qt::AlignLeft | Qt::AlignTop, "CLOCK:");

    for (int i = 0; i < transactionsVector.size(); ++i)
    {
        QRect textRect(175, 150, img.width() - 20, 20);
        painter.drawText(textRect, Qt::AlignLeft | Qt::AlignTop, transactionsVector[i]);
    }

    QRect textRect8(10, 180, img.width() - 20, 20);
    painter.drawText(textRect8, Qt::AlignLeft | Qt::AlignTop, "VESA");

    QRect textRect9(50, 180, img.width() - 20, 20);
    painter.drawText(textRect9, Qt::AlignLeft | Qt::AlignTop, type);

    QRect textRect10(10, 210, img.width() - 20, 20);
    painter.drawText(textRect10, Qt::AlignLeft | Qt::AlignTop, "CARD NUMBER");

    serial.replace(0, 5, "XXXXX");

    QRect textRect11(10, 210, img.width() - 20, 20);
    painter.drawText(textRect11, Qt::AlignRight | Qt::AlignTop, serial);

    QRect textRect14(10, 240, img.width() - 20, 20);
    painter.drawText(textRect14, Qt::AlignLeft | Qt::AlignTop, "TRANSACTION");

    QRect textRect15(10, 270, img.width() - 20, 20);
    painter.drawText(textRect15, Qt::AlignRight | Qt::AlignTop, QString::number(transaction));

    QRect textRect19(10, img.height() - 80, img.width() - 20, 20);
    painter.drawText(textRect19, Qt::AlignLeft | Qt::AlignBottom, "---------------------------------------------------------------------");

    QRect textRect20(10, img.height() - 60, img.width() - 20, 20);
    painter.drawText(textRect20, Qt::AlignLeft | Qt::AlignBottom, "TOTAL:");

    QRect textRect21(10, img.height() - 60, img.width() - 20, 20);
    painter.drawText(textRect21, Qt::AlignRight | Qt::AlignBottom, "XXXXXXXX");

    painter.end();

    QLabel *label = new QLabel(this);
    label->setPixmap(QPixmap::fromImage(img));
    layout->addWidget(label);
    setLayout(layout);

    qDebug() << "Ikkunan koko:" << this->size();
}
