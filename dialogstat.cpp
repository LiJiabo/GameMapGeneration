#include "dialogstat.h"
#include "ui_dialogstat.h"

DialogStat::DialogStat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStat)
{
    ui->setupUi(this);
}

DialogStat::~DialogStat()
{
    delete ui;
}

void DialogStat::on_pushButtonOK_clicked()
{
    emit windowClose();
}

