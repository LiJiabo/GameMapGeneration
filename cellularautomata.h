#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#include "abstractbot.h"

class CellularAutomata : public AbstractBot
{
public:
    CellularAutomata();
    CellularAutomata(int botNum,string botName,int botPos[2],BotType botType);
    //int next;//周围点亮的像素点个数
     vector<Operation> back;
    vector<Operation> play(int next);//............
    int get_next(vector<Operation> back);//获得周围像素点状态
};

#endif // CELLULARAUTOMATA_H
