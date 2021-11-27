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
        dialogNewBots=new DialogNewBots(i,this);
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
    int turn = 0;
    for(;turn<=100;turn++)
    {
        for(AbstractBot* botP:bots)
        {
            vector<Operation> operations(botP->play(formgamedisplay->map,mapWidth,mapHeight));
            //parse
            for(Operation& operation:operations)
            {
                if(operation.cmd=="lightUp")
                {
                    //获取坐标，画图
                    formgamedisplay->map.at(operation.pos[1]*mapWidth+operation.pos[0])->setColor(Qt::white);
                }
                else if(operation.cmd=="maintain")
                {
                    ;
                }
                else if(operation.cmd=="putOut")
                {
                    formgamedisplay->map.at(operation.pos[1]*mapWidth+operation.pos[0])->setColor(Qt::black);
                }
            }
        }
        //update
        formgamedisplay->update();
    }
}

