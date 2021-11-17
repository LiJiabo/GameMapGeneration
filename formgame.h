#ifndef FORMGAME_H
#define FORMGAME_H

#include <QWidget>
#include <QPainter>
#include <formgamedisplay.h>
#include <dialogbotsettings.h>

namespace Ui {
class FormGame;
}

class FormGame : public QWidget
{
    Q_OBJECT

public:
    explicit FormGame(int mapWidth,int mapHeight,QWidget *parent = nullptr);
    ~FormGame();


private:
    Ui::FormGame *ui;
    FormGameDisplay* formgamedisplay;
    DialogBotSettings* dialogbotsettings;
    int widthFG,heightFG;//FormGame宽高，以像素为单位
    const int margin=70;
    int mapWidth,mapHeight;//地图宽高，以格为单位

protected:
    void resizeEvent(QResizeEvent*);//调整游戏地图区域的大小

private slots:
    void on_pushButtonBotSettings_clicked();

signals:
    //void dialogBotSettingsOpen();
};

#endif // FORMGAME_H
