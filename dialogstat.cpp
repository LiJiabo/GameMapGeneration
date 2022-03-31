#include "dialogstat.h"
#include "ui_dialogstat.h"
#include "formgame.h"
#include <QString>
#include <cmath>

DialogStat::DialogStat(FormGame* formGame, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStat)
{
    ui->setupUi(this);
    ui->labelBotNum->setText(QString::number(formGame->getBotNum()));
    ui->labelWidth->setText(QString::number(formGame->mapWidth));
    ui->labelHeight->setText(QString::number(formGame->mapHeight));
    int white=formGame->getWhite();
    int black=formGame->mapWidth*formGame->mapHeight-white;
    ui->labelWhite->setText(QString::number(white));
    ui->labelBlack->setText(QString::number(black));
    ui->labelBalance->setText(QString::number(100-100*abs(white-black)/double(formGame->mapWidth*formGame->mapHeight))+QString("%"));
}

DialogStat::~DialogStat()
{
    delete ui;
}

void DialogStat::on_pushButtonOK_clicked()
{
    emit windowClose();
}

