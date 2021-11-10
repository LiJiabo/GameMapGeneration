#include "dialognewgame.h"
#include "ui_dialognewgame.h"

DialogNewGame::DialogNewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewGame)
{
    ui->setupUi(this);
    on_comboBoxBotType_currentTextChanged(ui->comboBoxBotType->currentText());//初始化Bot来源部分
}

DialogNewGame::~DialogNewGame()
{
    delete ui;
}

void DialogNewGame::on_pushButtonCancel_clicked()
{
    emit windowClose();
}

void DialogNewGame::on_pushButtonOK_clicked()
{
    //获取参数
    int mapWidth=ui->spinBoxMapSizeWidth->value();
    int mapHeight=ui->spinBoxMapSizeHeight->value();

    emit formGameOpen(mapWidth,mapHeight);
}

void DialogNewGame::on_comboBoxBotType_currentTextChanged(const QString &arg1)//更新Bot来源部分
{
    if(arg1=="内置")
    {
        ui->comboBoxBuiltIn->show();
        ui->lineEditFromFile->hide();
        ui->pushButtonNew->hide();
    }
    else if(arg1=="从文件")
    {
        ui->comboBoxBuiltIn->hide();
        ui->lineEditFromFile->show();
        ui->pushButtonNew->hide();
    }
    else//新建
    {
        ui->comboBoxBuiltIn->hide();
        ui->lineEditFromFile->hide();
        ui->pushButtonNew->show();
    }
}
