#ifndef BINARYMAPUNIT_H
#define BINARYMAPUNIT_H

#include "abstractmapunit.h"

const QColor colorTrue=QColor("green");
const QColor colorFalse=QColor("black");

class BinaryMapUnit : public AbstractMapUnit
{
public:
    BinaryMapUnit();
    QColor getColor();
protected:
    bool state;
};

#endif // BINARYMAPUNIT_H
