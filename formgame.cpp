#include "formgame.h"
#include "ui_formgame.h"

FormGame::FormGame(int mapWidth,int mapHeight,int botNum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGame)
{
    ui->setupUi(this);
    this->mapWidth=mapWidth;
    this->mapHeight=mapHeight;
    widthFG=this->width();//FormGame宽，以像素为单位
    heightFG=this->height();//FormGame高，以像素为单位
    this->botNum=botNum;

    //创建Bot
    for(int i=0;i<botNum;i++)
    {
        dialogNewBots=new DialogNewBots(i,mapWidth,mapHeight,this);
        connect(dialogNewBots,&DialogNewBots::windowClose,this,[=](){
            dialogNewBots->close();
            delete dialogNewBots;
            dialogNewBots=nullptr;
        });
        //暂时只能初始化CELLULARAUTOMATA类，后续需要增加(根据类名创建变量)!!!!!!!!!!!!!!!
        connect(dialogNewBots,&DialogNewBots::windowSuccess,this,[=](int botNum,QString botName,int botPos[2],BotType botType){
            bots.push_back(new CellularAutomata(botNum,botName,botPos));
            dialogNewBots->close();
            delete dialogNewBots;
            dialogNewBots=nullptr;
        });
        dialogNewBots->exec();
    }

    //画formgamedisplay
    formgamedisplay=new FormGameDisplay(mapWidth,mapHeight,this);
    formgamedisplay->setGeometry(margin,margin,widthFG-2*margin,heightFG-2*margin);

}

FormGame::~FormGame()
{
    delete ui;
}

void FormGame::resizeEvent(QResizeEvent*)//调整窗口大小后重绘棋盘
{
    widthFG=this->width();
    heightFG=this->height();
    if(formgamedisplay!=nullptr)
        formgamedisplay->setGeometry(margin,margin,widthFG-2*margin,heightFG-2*margin);
}

void FormGame::on_pushButtonBotSettings_clicked()//打开Bot设置窗口
{
    dialogbotsettings = new DialogBotSettings();
    connect(dialogbotsettings,&DialogBotSettings::windowClose,this,[=](){//关闭Bot设置窗口槽函数
        dialogbotsettings->close();
        delete dialogbotsettings;
        dialogbotsettings=nullptr;
    });
    connect(dialogbotsettings,&DialogBotSettings::windowSuccess,this,[=](){//保存参数并关闭窗口
        //...
        dialogbotsettings->close();
        delete dialogbotsettings;
        dialogbotsettings=nullptr;
    });
    dialogbotsettings->open();
}

void FormGame::on_play_clicked()
{
    //启动Play线程
    play=new Play(this);
    play->start();
}

vector<AbstractBot*>& FormGame::getBots()
{
    return bots;
}

FormGameDisplay* FormGame::getFormGameDisplay()
{
    return formgamedisplay;
}
