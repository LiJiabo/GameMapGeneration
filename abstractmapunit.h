#ifndef ABSTRACTMAPUNIT_H
#define ABSTRACTMAPUNIT_H

#include <QColor>

class AbstractMapUnit
{
public:
    AbstractMapUnit();
    AbstractMapUnit(int pos[2]);
    int pos[2];//pos[0]:x, pos[1]:y
    QColor getColor();
    void setColor(QColor color);
protected:
    QColor color=Qt::black;
};

#endif // ABSTRACTMAPUNIT_H
