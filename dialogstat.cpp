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
    this->white=formGame->getWhite();
    this->black=formGame->mapWidth*formGame->mapHeight-(this->white);
    ui->labelWhite->setText(QString::number(white));
    ui->labelBlack->setText(QString::number(black));
    balance=100-100*abs(white-black)/double(formGame->mapWidth*formGame->mapHeight);
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
    this->smooth=res;
    //显示结果
    ui->pushButtonSmooth->deleteLater();
    QLabel* label=new QLabel("result");
    ui->gridLayout->addWidget(label,6,1);
    label->setText(QString::number(res));
}


void DialogStat::on_pushButtonLog_clicked()
{
    QString filename("./gameMapGenRule2StatLog.csv");//只在一个演示内有效
    QFile file(filename);
    if(!file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::warning(this,"错误","无法打开gameMapGenRule2StatLog.csv文件进行写入");
        return;
    }
    QTextStream out(&file);
    //暂时没有创建表头
    //隐含表头：CellularAutomata的threshold数，亮点，暗点，平衡性，顺滑度
    vector<AbstractBot*>& bots=formGame->getBots();
    if(bots.size()>0)
    {
        out << *(bots.at(0)->getThreshold());
    }
    else
    {
        QMessageBox::warning(this,"错误","Bot数为0！");
        return;
    }
    out << "," << white << "," << black << "," << balance/100.0 << "," << smooth << "\n";
    file.close();

    QMessageBox::information(this,"成功","Bot threshold和统计数据已存储到gameMapGenRule2StatLog.csv文件");
}


void DialogStat::on_pushButtonTrain_clicked()
{
    //生成Python脚本
    QString filename="./gameMapGenTrain.py";
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","无法打开gameMapGenTrain.py文件进行写入！");
        return;
    }
    QTextStream out(&file);
    out << "import pandas as pd\n";
    out << "import torch\n";
    out << "import torch.nn as nn\n";
    out << "import matplotlib.pyplot as plt\n";
    out << "\n";
    out << "# data_path = \"/Users/lijiabo/Documents/GitHub/build-GameMapGeneration-Qt_6_2_3_for_macOS-Debug/GameMapGeneration.app/Contents/MacOS/gameMapGenRule2StatLog.csv\"\n";
    out << "data_path = \'./gameMapGenRule2StatLog.csv\'\n";
    out << "try:\n";
    out << "    data = pd.read_csv(data_path, header=None)\n";
    out << "except FileNotFoundError:\n";
    out << "    print(\"Error: can not find the file: \", data_path)\n";
    out << "    exit()\n";
    out << "data.columns = [\'threshold\', \'white\', \'black\', \'balance\', \'smooth\']\n";
    out << "\n";
    out << "batch_size = 1\n";
    out << "num_epochs = 200\n";
    out << "learning_rate = 0.01\n";
    out << "\n";
    out << "# 预测balance\n";
    out << "balance_model = nn.Sequential(\n";
    out << "    nn.Linear(1, 5),\n";
    out << "    nn.ReLU(),\n";
    out << "    nn.Linear(5, 4),\n";
    out << "    nn.ReLU(),\n";
    out << "    nn.Linear(4, 1),\n";
    out << "    nn.Sigmoid()\n";
    out << ")\n";
    out << "optimizer = torch.optim.Adam(balance_model.parameters(), lr=learning_rate)\n";
    out << "criterion = nn.MSELoss()\n";
    out << "\n";
    out << "losses_balance = []\n";
    out << "\n";
    out << "for i in range(num_epochs):\n";
    out << "    for j in range(len(data)):\n";
    out << "        threshold = data.iloc[j, 0]\n";
    out << "        balance = data.iloc[j, 3]\n";
    out << "\n";
    out << "        balance_model.zero_grad()\n";
    out << "        input = torch.tensor([[threshold]], dtype=torch.float)\n";
    out << "        output = balance_model(input)\n";
    out << "        loss = criterion(output, torch.tensor([[balance]], dtype=torch.float))\n";
    out << "        loss.backward()\n";
    out << "        optimizer.step()\n";
    out << "        print(f\'Balance: epoch:{i}, loss:\', loss.item())\n";
    out << "    losses_balance.append(loss.item())\n";
    out << "\n";
    out << "# 预测smooth\n";
    out << "smooth_model = nn.Sequential(\n";
    out << "    nn.Linear(1, 5),\n";
    out << "    nn.ReLU(),\n";
    out << "    nn.Linear(5, 4),\n";
    out << "    nn.ReLU(),\n";
    out << "    nn.Linear(4, 1),\n";
    out << "    nn.Sigmoid()\n";
    out << ")\n";
    out << "optimizer = torch.optim.Adam(balance_model.parameters(), lr=learning_rate)\n";
    out << "criterion = nn.MSELoss()\n";
    out << "\n";
    out << "losses_smooth = []\n";
    out << "\n";
    out << "for i in range(num_epochs):\n";
    out << "    for j in range(len(data)):\n";
    out << "        threshold = data.iloc[j, 0]\n";
    out << "        smooth = data.iloc[j, 4]\n";
    out << "\n";
    out << "        smooth_model.zero_grad()\n";
    out << "        input = torch.tensor([[threshold]], dtype=torch.float)\n";
    out << "        output = smooth_model(input)\n";
    out << "        loss = criterion(output, torch.tensor([[smooth]], dtype=torch.float))\n";
    out << "        loss.backward()\n";
    out << "        optimizer.step()\n";
    out << "        print(f\'Smooth: epoch:{i}, loss:\', loss.item())\n";
    out << "    losses_smooth.append(loss.item())\n";
    out << "\n";
    out << "plt.plot(losses_balance)\n";
    out << "plt.plot(losses_smooth)\n";
    out << "plt.legend([\'balance\', 'smooth\'], loc=\'upper right\')\n";
    out << "plt.show()\n";

    file.close();

    //执行脚本
    system("/Users/lijiabo/miniconda3/bin/python ./gameMapGenTrain.py");
}
