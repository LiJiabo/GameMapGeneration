#ifndef ABSTRACTBOT_H
#define ABSTRACTBOT_H

#include <string>
#include <vector>
#include <QString>
#include "abstractmapunit.h"
using namespace std;

enum BotType{CELLULARAUTOMATA};//deprecated

struct Operation
{
    int pos[2];
    QString cmd;//要执行的命令，传入mapunit类，由其进行解释
};

class AbstractBot
{
public:
    AbstractBot();
    AbstractBot(int botNum,QString botName,int botPos[2],BotType botType,int threshold);
    int botNum;
    QString botName;
    int botPos[2];
    BotType botType;//deprecated
    int threshold;
    virtual vector<Operation> play(vector<AbstractMapUnit*>, int mapWidth, int mapHeight)=0;
    virtual int* getThreshold();
};

#endif // ABSTRACTBOT_H
