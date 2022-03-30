#include "dialogbotsettings.h"
#include "ui_dialogbotsettings.h"

DialogBotSettings::DialogBotSettings(int mapWidth, int mapHeight, vector<AbstractBot*> bots, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBotSettings)
{
    ui->setupUi(this);
    this->mapWidth=mapWidth;
    this->mapHeight=mapHeight;
    this->bots=bots;
    ui->tableWidget->setColumnCount(mapWidth);
    ui->tableWidget->setRowCount(mapHeight);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改表格
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使表格列平均分布
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使表格行平均分布
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//只能选中1个
    QStringList horizontalHeader, verticalHeader;
    for(int i=0;i<mapWidth;i++)
        horizontalHeader.push_back(QString::number(i));
    ui->tableWidget->setHorizontalHeaderLabels(horizontalHeader);//设置水平表头
    for(int i=0;i<mapHeight;i++)
        verticalHeader.push_back(QString::number(i));
    ui->tableWidget->setVerticalHeaderLabels(verticalHeader);//设置纵向表头
    //画出已有的bot
    for(AbstractBot* p:bots)
    {
        QTableWidgetItem* twi=new QTableWidgetItem();
        twi->setBackground(Qt::blue);
        ui->tableWidget->setItem(p->botPos[0],p->botPos[1],twi);
    }
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
    emit windowSuccess();
}

void DialogBotSettings::on_tableWidget_cellClicked(int row, int column)
{
    AbstractBot* ptr=nullptr;
    bool ifFound=false;
    for(AbstractBot* p:bots)
    {
        if(p->botPos[0]==row&&p->botPos[1]==column)
        {
            ptr=p;
            ui->lineEditBotNum->setText(QString::number(ptr->botNum));
            ui->lineEditBotName->setText(ptr->botName);
            ui->lineEditX->setText(QString::number(ptr->botPos[1]));
            ui->lineEditY->setText(QString::number(ptr->botPos[0]));
            ifFound=true;
            break;
        }
    }
    if(!ifFound)
    {
        ui->lineEditBotNum->setText("");
        ui->lineEditBotName->setText("");
        ui->lineEditX->setText("");
        ui->lineEditY->setText("");
    }
}
