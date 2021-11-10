#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionGame,&QAction::triggered,this,[=](){//打开新建游戏窗口
        dialognewgame=new DialogNewGame(this);
        connect(dialognewgame,&DialogNewGame::windowClose,this,[=](){//关闭新建游戏窗口
            dialognewgame->close();
            delete dialognewgame;
            dialognewgame=nullptr;
        });
        connect(dialognewgame,&DialogNewGame::formGameOpen,this,[=](int mapWidth,int mapHeight){//打开游戏界面
            dialognewgame->close();
            delete dialognewgame;
            dialognewgame=nullptr;
            formgame=new FormGame(mapWidth,mapHeight);
            formgame->show();
        });
        dialognewgame->open();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Consolas",20));
    painter.drawText(rect(),Qt::AlignCenter,"GameMapGeneration V0.0.1");
}
