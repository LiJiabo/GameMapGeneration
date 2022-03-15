#include "formgamedisplay.h"
#include "ui_formgamedisplay.h"

FormGameDisplay::FormGameDisplay(int mapWidth,int mapHeight,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormGameDisplay)
{
    ui->setupUi(this);
    this->mapWidth=mapWidth;
    this->mapHeight=mapHeight;

    //设置map,现在还只是BinaryMapUnit，以后可以设置！！！！！！！！！！
    for(int i=0;i<mapHeight;i++)
        for(int j=0;j<mapWidth;j++)
        {
            int pos[2]={j,i};
            map.push_back(new BinaryMapUnit(pos));
        }
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

    for(AbstractMapUnit* ptr:map)
    {
        if(ptr->pos[0]==5&&ptr->pos[1]==2&&ptr->getColor()==Qt::white)
        {
            qDebug("test");//没有？？？
        }
        painter.setBrush(ptr->getColor());
        painter.drawRect(leftTopX(ptr->pos[0]),leftTopY(ptr->pos[1]),widthPx/double(mapWidth),heightPx/double(mapHeight));
    }

}

void FormGameDisplay::updateMap()
{
    update(rect());
}
