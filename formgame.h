#ifndef FORMGAME_H
#define FORMGAME_H

#include <QWidget>
#include <QPainter>
#include <QThread>
#include <formgamedisplay.h>
#include <dialogbotsettings.h>
#include <abstractbot.h>
#include <cellularautomata.h>
#include <dialognewbots.h>
#include "binarymapunit.h"
#include <vector>
#include "play.h"
#include <dialogstat.h>
using namespace std;

namespace Ui {
class FormGame;
}

class Play;

class FormGame : public QWidget
{
    Q_OBJECT

public:
    explicit FormGame(int mapWidth,int mapHeight,int botNum,QWidget *parent = nullptr);
    ~FormGame();
    vector<AbstractBot*>& getBots();
    FormGameDisplay* getFormGameDisplay();
    int mapWidth,mapHeight;//地图宽高，以格为单位

private:
    Ui::FormGame *ui;
    FormGameDisplay* formgamedisplay;
    DialogBotSettings* dialogbotsettings;
    DialogStat* dialogstat;
    int widthFG,heightFG;//FormGame宽高，以像素为单位
    const int margin=70;
    int botNum;//Bot数量，可以变化
    vector<AbstractBot*> bots;//存储所有的Bot
    DialogNewBots* dialogNewBots;
    int dialogNewBotsCount=0;
    Play* play=nullptr;
    vector<vector<bool>>* selected=nullptr;

protected:
    void resizeEvent(QResizeEvent*);//调整游戏地图区域的大小

private slots:
    void on_pushButtonBotSettings_clicked();
    void on_play_clicked();
    void on_pause_clicked();

    void on_pushButtonStat_clicked();

signals:
    //void dialogBotSettingsOpen();
};

#endif // FORMGAME_H
