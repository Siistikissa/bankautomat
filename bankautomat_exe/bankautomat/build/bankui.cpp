#include "bankui.h"
#include "ui_bankui.h"

bankUI::bankUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::bankUI)
{
    ui->setupUi(this);
}

bankUI::~bankUI()
{
    delete ui;
}
