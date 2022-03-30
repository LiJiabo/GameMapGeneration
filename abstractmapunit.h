#ifndef ABSTRACTMAPUNIT_H
#define ABSTRACTMAPUNIT_H

#include <QColor>

class AbstractMapUnit
{
public:
    AbstractMapUnit();
    AbstractMapUnit(int pos[2]);
    int pos[2];
    /* 本程序代码位置相关变量定义说明
     * pos[2]变量：和地图对应，横向的行<----->地图上横向的行，
     *                      纵向的列<----->地图上纵向的列
     * x、y变量：和Qt的坐标系统对应，x代表横轴，y代表纵轴
     * o--------------> x轴
     * ⎢
     * ⎜
     * ⎜
     * ⎜
     * ↓
     * y轴
     * pos[0]代表y，pos[1]代表x
     */
    QColor getColor();
    void setColor(QColor color);
protected:
    QColor color=Qt::black;
};

#endif // ABSTRACTMAPUNIT_H
