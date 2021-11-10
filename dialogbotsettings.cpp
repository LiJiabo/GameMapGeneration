#include "dialogbotsettings.h"
#include "ui_dialogbotsettings.h"

DialogBotSettings::DialogBotSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBotSettings)
{
    ui->setupUi(this);
}

DialogBotSettings::~DialogBotSettings()
{
    delete ui;
}

void DialogBotSettings::on_pushButton_2_clicked()//取消
{
    emit windowClose();
}


void DialogBotSettings::on_pushButton_clicked()//确认
{
    emit windowSuccess();
}

