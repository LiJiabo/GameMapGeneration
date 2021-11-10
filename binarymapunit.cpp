#include "binarymapunit.h"

BinaryMapUnit::BinaryMapUnit()
{
    this->state=false;
}

QColor BinaryMapUnit::getColor()
{
    if(state)
        return colorTrue;
    return colorFalse;
}
