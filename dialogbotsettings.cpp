#include "dialogbotsettings.h"
#include "ui_dialogbotsettings.h"
#include <all.h>
#include <QDebug>
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

    //获取参数
    for(unsigned int i=0;i<bot_state.size();i++)
    {
        if(ui->start_x->text().toInt()==bot_state[i].pos[0]&&ui->start_y->text().toInt()==bot_state[i].pos[1])
            bot_state[i].cmd="light";
    }
    // bot_state.push_back(ui->start_x->text().toInt());
    // bot_state.push_back(ui->start_y->text().toInt());
    emit windowSuccess();
    //测试bot_state数组中的内容
    //for(int i=0;i<(int)bot_state.size();i++)
    //qDebug()<<bot_state[i];
}

