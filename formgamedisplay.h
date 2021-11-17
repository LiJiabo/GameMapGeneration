#ifndef FORMGAMEDISPLAY_H
#define FORMGAMEDISPLAY_H

#include <QWidget>
#include <QPainter>

namespace Ui {
class FormGameDisplay;
}

class FormGameDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit FormGameDisplay(int mapWidth,int mapHeight,QWidget *parent = nullptr);
    ~FormGameDisplay();

private:
    Ui::FormGameDisplay *ui;
    int mapWidth,mapHeight;//地图宽高，以格为单位
protected:
    void paintEvent(QPaintEvent*);
};

#endif // FORMGAMEDISPLAY_H
