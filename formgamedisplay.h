#ifndef FORMGAMEDISPLAY_H
#define FORMGAMEDISPLAY_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include "abstractmapunit.h"
#include "binarymapunit.h"
#define leftTopX(x) (widthPx/double(mapWidth)*(x))
#define leftTopY(y) (heightPx/double(mapHeight)*(y))
using namespace std;

namespace Ui {
class FormGameDisplay;
}

class FormGameDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit FormGameDisplay(int mapWidth,int mapHeight,QWidget *parent = nullptr);
    ~FormGameDisplay();
    void updateMap();
    vector<AbstractMapUnit*> map;

private:
    Ui::FormGameDisplay *ui;
    int mapWidth,mapHeight;//地图宽高，以格为单位

protected:
    void paintEvent(QPaintEvent*);
};

#endif // FORMGAMEDISPLAY_H
