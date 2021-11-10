#include "formgame.h"
#include "ui_formgame.h"
#include <all.h>
FormGame::FormGame(int mapWidth,int mapHeight,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGame)
{
    ui->setupUi(this);
    this->mapWidth=mapWidth;
    this->mapHeight=mapHeight;
    widthFG=this->width();
    heightFG=this->height();
    initialize(mapWidth,mapHeight);
    connect(ui->play,&QPushButton::clicked,this,[=](){

        for( unsigned int i=0;i<bot_state.size();i++)
        {
            int accont=0;
            if(bot_state[i].pos[0]-1>0){
                if(bot_state[i-1].cmd=="light")
                    accont++;
            }

        }
    });
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
