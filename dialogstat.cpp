#include "dialogstat.h"
#include "ui_dialogstat.h"
#include "formgame.h"
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QFileInfo>
#include <cmath>
#include <cstdlib>

DialogStat::DialogStat(FormGame* formGame, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStat)
{
    ui->setupUi(this);
    ui->labelBotNum->setText(QString::number(formGame->getBotNum()));
    ui->labelWidth->setText(QString::number(formGame->mapWidth));
    ui->labelHeight->setText(QString::number(formGame->mapHeight));
    int white=formGame->getWhite();
    int black=formGame->mapWidth*formGame->mapHeight-white;
    ui->labelWhite->setText(QString::number(white));
    ui->labelBlack->setText(QString::number(black));
    ui->labelBalance->setText(QString::number(100-100*abs(white-black)/double(formGame->mapWidth*formGame->mapHeight))+QString("%"));
    this->formGame=formGame;
}

DialogStat::~DialogStat()
{
    delete ui;
}

void DialogStat::on_pushButtonOK_clicked()
{
    emit windowClose();
}


void DialogStat::on_pushButtonSmooth_clicked()
{
    ui->pushButtonSmooth->setText("计算中...");
    //用Python计算顺滑度
    vector<vector<int>>& digitMap=formGame->getFormGameDisplay()->getDigitMap();
    //导出csv文件
    QString filename("./gameMapGenDigitMap.csv");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","无法打开gameMapGenDigitMap.csv文件进行写入");
        return;
    }
    QTextStream out(&file);
    //创建表头
    out<<"0";
    for(int i=1;i<formGame->mapWidth;i++)
    {
        out<<","<<QString::number(i);
    }
    out<<"\n";
    //写入内容
    for(int i=0;i<formGame->mapHeight;i++)
    {
        out<<digitMap.at(i).at(0);
        for(int j=1;j<formGame->mapWidth;j++)
        {
            out<<","<<digitMap.at(i).at(j);
        }
        out<<"\n";
    }
    QFileInfo info(file);
    qDebug()<<info.absoluteFilePath();
    file.close();
    //生成Python脚本
    QString pyfilename("./gameMapGenSmooth.py");
    QFile pyfile(pyfilename);
    if(!pyfile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","无法打开gameMapGenSmooth.py文件进行写入");
        return;
    }
    QTextStream pyout(&pyfile);
    pyout<<"import pandas as pd\n";
    pyout<<"from sklearn.cluster import *\n\n";
    pyout<<"digit_map_path = \"./gameMapGenDigitMap.csv\";\n";
    pyout<<"digit_map = pd.read_csv(digit_map_path)\n";
    pyout<<"pos_list = []\n";
    pyout<<"for i in range(digit_map.shape[0]):\n";
    pyout<<"\tfor j in range(digit_map.shape[1]):\n";
    pyout<<"\t\tif digit_map.iloc[i,j] == 1:\n";
    pyout<<"\t\t\tpos_list.append([i,j])\n";
    pyout<<"db = DBSCAN(eps=1.5, min_samples=1).fit(pos_list)\n";
    pyout<<"file=open(\"./gameMapGenCluster.csv\",\"w\")\n";
    pyout<<"file.write(str(len(set(db.labels_))))\n";
    pyfile.close();
    //调用Python脚本
    if(system("/Users/lijiabo/miniconda3/bin/python ./gameMapGenSmooth.py")!=0)
    {
        QMessageBox::warning(this,"错误","调用Python脚本错误");
        return;
    }
    //读取结果
    QString outfilename("./gameMapGenCluster.csv");
    QFile outfile(outfilename);
    if(!outfile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","无法打开gameMapGenCluster.csv文件进行读取");
        return;
    }
    QTextStream outin(&outfile);
    QString result;
    outin>>result;
    int res=result.toInt();
    //显示结果
    ui->pushButtonSmooth->deleteLater();
    QLabel* label=new QLabel("result");
    ui->gridLayout->addWidget(label,6,1);
    label->setText(QString::number(res));
}

