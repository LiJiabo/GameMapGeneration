#include "formgamedisplay.h"
#include "ui_formgamedisplay.h"

FormGameDisplay::FormGameDisplay(int mapWidth,int mapHeight,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGameDisplay)
{
    ui->setupUi(this);
    this->mapWidth=mapWidth;
    this->mapHeight=mapHeight;
}

FormGameDisplay::~FormGameDisplay()
{
    delete ui;
}

void FormGameDisplay::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    //初始设置
    painter.setPen(Qt::green);
    painter.setBrush(QBrush(Qt::black));
    //画背景
    painter.drawRect(rect());
    //画网格
    int widthPx=this->width();
    int heightPx=this->height();
    for(int i=0;i<mapWidth-1;i++)
        painter.drawLine(int(widthPx/double(mapWidth))*(i+1),0,int(widthPx/double(mapWidth))*(i+1),heightPx);//竖线
    /*
    //查看格子的像素点的横纵坐标
    // for(int i=-1;i<mapWidth;i++)
    //       qDebug()<<int(widthPx/double(mapWidth))*(i+1);
    */
    for(int i=0;i<mapHeight-1;i++)
        painter.drawLine(0,int(heightPx/double(mapHeight))*(i+1),widthPx,int(heightPx/double(mapHeight))*(i+1));//横线

    /*
    painter.setPen(Qt::red);
    //QPointF pointf[(int)bot_state.size()];//不是point
    for(int i=0;i<(int)bot_state.size();i++)
    {
        pointf[i].setX(int(widthPx/double(mapWidth))*bot_state[i].pos[0]);
        pointf[i].setY(int(heightPx/double(mapHeight))*bot_state[i].pos[1]);

    }

    for(int i=0;i<(int)bot_state.size();i++)
    {
        // qDebug()<<pointf[i];
        //painter.drawPoints(pointf,(int)bot_state.size());
        if(bot_state[i].cmd=="light")
            //painter.drawEllipse(int(widthPx/double(mapWidth))*(bot_state[i].pos[0]),int(heightPx/double(mapHeight))*bot_state[i].pos[1],12,12);
            painter.drawEllipse(pointf[i],12,12);
    }
    */
}
