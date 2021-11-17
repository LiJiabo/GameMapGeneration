#include "dialognewbots.h"
#include "ui_dialognewbots.h"

DialogNewBots::DialogNewBots(int botNum, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewBots)
{
    ui->setupUi(this);
    ui->labelBotNum->setText(QString::number(botNum));
    QString botCreateType = ui->comboBoxBotCreateType->currentText();
    if(botCreateType=="内置")
    {
        ui->label_5->setText("预设");
        ui->gridLayout->
    }
    else if(botCreateType=="从文件")
    {
        ui->label_5->setText("路径");
    }
    else if(botCreateType=="新建")
    {
        ui->label_5->setText("");
    }
}

DialogNewBots::~DialogNewBots()
{
    delete ui;
}

void DialogNewBots::on_pushButtonCancel_clicked()
{
    emit windowClose();
}


void DialogNewBots::on_pushButtonOK_clicked()
{
    emit windowSuccess();
}

