#ifndef ABSTRACTBOT_H
#define ABSTRACTBOT_H

#include <string>
#include <vector>
#include <QString>
#include "abstractmapunit.h"
using namespace std;

enum BotType{CELLULARAUTOMATA/*细胞自动机*/};

struct Operation
{
    int pos[2];
    QString cmd;//要执行的命令，传入mapunit类，由其进行解释
    //int next;//周围点的亮点数
};

class AbstractBot
{
public:
    AbstractBot();
    AbstractBot(int botNum,QString botName,int botPos[2],BotType botType);
    int botNum;
    QString botName;
    int botPos[2];//botPos[0]:x, botPos[1]:y
    BotType botType;
    virtual vector<Operation> play(vector<AbstractMapUnit*>, int mapWidth, int mapHeight)=0;
};

#endif // ABSTRACTBOT_H
