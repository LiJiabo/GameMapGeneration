#include "abstractmapunit.h"

AbstractMapUnit::AbstractMapUnit()
{

}

AbstractMapUnit::AbstractMapUnit(int pos[2])
{
    this->pos[0]=pos[0];
    this->pos[1]=pos[1];
}

QColor AbstractMapUnit::getColor()
{
    return color;
}

void AbstractMapUnit::setColor(QColor color)
{
    this->color=color;
}
