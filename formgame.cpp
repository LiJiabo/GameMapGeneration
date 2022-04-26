#include "formgame.h"
#include "ui_formgame.h"
#include <QFile>

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
        dialogNewBots=new DialogNewBots(i,mapWidth,mapHeight,selected,this);
        connect(dialogNewBots,&DialogNewBots::windowClose,this,[=](){
            dialogNewBots->close();
            delete dialogNewBots;
            dialogNewBots=nullptr;
        });
        //暂时只能初始化CELLULARAUTOMATA类，后续需要增加(根据类名创建变量)!!!!!!!!!!!!!!!
        connect(dialogNewBots,&DialogNewBots::windowSuccess,this,[this](int botNum,QString botName,int botPos[2],BotType botType)mutable{
            bots.push_back(new CellularAutomata(botNum,botName,botPos));
            dialogNewBots->close();
            delete dialogNewBots;
            dialogNewBots=nullptr;
            if(selected==nullptr)
                selected=new vector<vector<bool>>(this->mapHeight,vector<bool>(this->mapWidth,false));
            selected->at(botPos[0]).at(botPos[1])=true;
        });
        dialogNewBots->exec();
    }

    //画formgamedisplay
    formgamedisplay=new FormGameDisplay(mapWidth,mapHeight,this);
    formgamedisplay->setGeometry(margin,margin,widthFG-2*margin,heightFG-2*margin);

    //删除过期的gameMapGenRule2StatLog.csv文件
    QFile rule2StatLogFile("./gameMapGenRule2StatLog.csv");
    if(rule2StatLogFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        rule2StatLogFile.remove();
    }

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
    dialogbotsettings = new DialogBotSettings(mapWidth, mapHeight, bots);
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

void FormGame::on_pause_clicked()//暂停Play线程
{
//下一步：
//实现暂停功能✔️-->实现统计窗口✔️-->让平衡性实时更新，就用C++计算✔️-->加入顺滑度参数，需要点击“计算”按钮才能显示，且没有暂停的话会提示暂停✔️
//实现机器学习数据可视化-->实现Bot规则部分（机器学习）
    if(play->getState()==Play::RUNNING)
    {
        play->pause();
        ui->pause->setText("继续");
    }
    else if(play->getState()==Play::PAUSED)
    {
        play->resume();
        ui->pause->setText("暂停");
    }
}


void FormGame::on_pushButtonStat_clicked()//统计窗口
{
    dialogstat=new DialogStat(this, this);
    dialogstat->open();
    connect(dialogstat,&DialogStat::windowClose,this,[=](){
        dialogstat->close();
        delete dialogstat;
        dialogstat=nullptr;
    });
}

int FormGame::getBotNum() const
{
    return botNum;
}

int FormGame::getWhite() const
{
    int white=0;
    for(AbstractMapUnit* p:formgamedisplay->map)
    {
        if(p->getColor()==Qt::white)
            white++;
    }
    return white;
}
