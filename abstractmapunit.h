#ifndef ABSTRACTMAPUNIT_H
#define ABSTRACTMAPUNIT_H

#include <QColor>

class AbstractMapUnit
{
public:
    AbstractMapUnit();
    AbstractMapUnit(int pos[2]);
    int pos[2];//pos[0]:x, pos[1]:y
    virtual QColor getColor()=0;//获取显示颜色
};

#endif // ABSTRACTMAPUNIT_H
