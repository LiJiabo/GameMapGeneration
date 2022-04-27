#include "dialognewgame.h"
#include "ui_dialognewgame.h"

DialogNewGame::DialogNewGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewGame)
{
    ui->setupUi(this);
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
    int botNum=ui->spinBoxBotNum->value();
    int threshold=ui->spinBoxThreshold->value();

    emit formGameOpen(mapWidth,mapHeight,botNum,threshold);
}
