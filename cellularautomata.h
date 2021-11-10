#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#include "abstractbot.h"

class CellularAutomata : public AbstractBot
{
public:
    CellularAutomata();
    CellularAutomata(int botNum,string botName,int botPos[2],BotType botType);
    vector<Operation> play(bool nearMap[9]);//............
};

#endif // CELLULARAUTOMATA_H
