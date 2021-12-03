#ifndef CELLULARAUTOMATA_H
#define CELLULARAUTOMATA_H

#include "abstractbot.h"

class CellularAutomata : public AbstractBot
{
public:
    CellularAutomata();
    CellularAutomata(int botNum,QString botName,int botPos[2]);
    //int next;//周围点亮的像素点个数
    vector<Operation> back;
    vector<Operation> play(vector<AbstractMapUnit*>, int mapWidth, int mapHeight);
    //int get_next(vector<Operation> back);//获得周围像素点状态
    const int threshhold=5;
};

#endif // CELLULARAUTOMATA_H
