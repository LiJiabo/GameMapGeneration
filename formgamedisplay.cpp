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
        painter.drawLine(int(widthPx/double(mapWidth))*(i+1),0,int(widthPx/double(mapWidth))*(i+1),heightPx);
    for(int i=0;i<mapHeight-1;i++)
        painter.drawLine(0,int(heightPx/double(mapHeight))*(i+1),widthPx,int(heightPx/double(mapHeight))*(i+1));
}
