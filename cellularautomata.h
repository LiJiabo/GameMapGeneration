#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#include "abstractbot.h"

class CellularAutomata : public AbstractBot
{
public:
    CellularAutomata();
    CellularAutomata(int botNum,QString botName,int botPos[2]);
    vector<Operation> back;
    vector<Operation> play(vector<AbstractMapUnit*>, int mapWidth, int mapHeight);
    const int threshhold=5;
};

#endif // CELLULARAUTOMATA_H
