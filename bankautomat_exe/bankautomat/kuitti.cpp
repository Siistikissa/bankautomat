#include "kuitti.h"
#include "ui_kuitti.h"

Kuitti::Kuitti(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Kuitti)
{
    printtaus.setSource(QUrl::fromLocalFile("C:\\projektit\\pankkiautomaatti\\SPL_Group8\\bankautomat_exe\\bankautomat\\printtaus.wav"));
    printtaus.setVolume(1.0);
    ui->setupUi(this);
    printtaus.play();
}

Kuitti::~Kuitti()
{
    delete ui;
}
