#include "kuitti.h"
#include "ui_kuitti.h"

Kuitti::Kuitti(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kuitti)
{
    QDir directory("../bankautomat/");
    QString pathToPrint = directory.absoluteFilePath("printtaus.wav");
    printtaus.setSource(QUrl::fromLocalFile(pathToPrint));
    printtaus.setVolume(1.0);
    ui->setupUi(this);
    printtaus.play();
}

Kuitti::~Kuitti()
{
    delete ui;
}
