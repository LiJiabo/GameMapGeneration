#include "dialognewbots.h"
#include "ui_dialognewbots.h"

DialogNewBots::DialogNewBots(int botNum, int mapWidth, int mapHeight, vector<vector<bool>>* selected, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewBots)
{
    ui->setupUi(this);
    ui->labelBotNum->setText(QString::number(botNum));
    ui->lineEditBotName->setText(QString::number(botNum));
    ui->comboBoxBotCreateType->setCurrentText("内置");
    ui->label_5->setText("预设");
    dynamicWidget=new QComboBox;
    ui->gridLayout->addWidget(dynamicWidget,6,1);
    QComboBox* dynamicComboBox=dynamic_cast<QComboBox*>(dynamicWidget);
    if(dynamicComboBox!=nullptr)
        dynamicComboBox->addItems(builtinBotTypes);
    else
        throw "dynamic cast(from QWidget* to QComboBox*) failed!";

    this->mapWidth=mapWidth;
    this->mapHeight=mapHeight;
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
    if(selected!=nullptr)
        for(int i=0;i<mapHeight;i++)//使已选择的单元格变色
            for(int j=0;j<mapWidth;j++)
                if(selected->at(i).at(j))
                {
                    QTableWidgetItem* p=new QTableWidgetItem();
                    p->setBackground(Qt::blue);
                    ui->tableWidget->setItem(i,j,p);
                }
}

DialogNewBots::~DialogNewBots()
{
    delete ui;
}

void DialogNewBots::on_pushButtonCancel_clicked()
{
    emit windowClose();
}


void DialogNewBots::on_pushButtonOK_clicked()
{
    //暂时只能是CELLULARAUTOMATA类型，接下来还要考虑怎么确定其他类型!!!!!!!!!!!!!!!!!
    //Temporary
    BotType botType=CELLULARAUTOMATA;
    //
    int botPos[2]={ui->spinBoxX->value(),ui->spinBoxY->value()};
    emit windowSuccess(ui->labelBotNum->text().toInt(),ui->lineEditBotName->text(),botPos,botType);
}

void DialogNewBots::on_comboBoxBotCreateType_currentTextChanged(const QString &arg1)
{
    if(arg1=="内置")
    {
        ui->label_5->setText("预设");
        ui->gridLayout->removeWidget(dynamicWidget);
        delete dynamicWidget;
        ui->gridLayout->addWidget((dynamicWidget=new QComboBox),6,1);
        //向combo box中添加项目
        QComboBox* dynamicComboBox=dynamic_cast<QComboBox*>(dynamicWidget);
        if(dynamicComboBox!=nullptr)
            dynamicComboBox->addItems(builtinBotTypes);
        else
            throw "dynamic cast(from QWidget* to QComboBox*) failed!";
    }
    else if(arg1=="从文件")
    {
        ui->label_5->setText("路径");
        ui->gridLayout->removeWidget(dynamicWidget);
        delete dynamicWidget;
        ui->gridLayout->addWidget((dynamicWidget=new QLineEdit),6,1);
    }
    else if(arg1=="自定义")
    {
        ui->label_5->setText("");
        ui->gridLayout->removeWidget(dynamicWidget);
        delete dynamicWidget;
        ui->gridLayout->addWidget((dynamicWidget=new QPushButton("设置规则")),6,1);
    }
}

void DialogNewBots::on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int, int)
{
    ui->spinBoxX->setValue(currentRow);
    ui->spinBoxY->setValue(currentColumn);
}

