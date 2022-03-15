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
    AbstractBot(int botNum,QString botName,int botPos[2],BotType botType);
    int botNum;
    QString botName;
    int botPos[2];
    BotType botType;//deprecated
    //可能不需要改成这个
    //int rule[2]={0};//两个数字组成保留 闭 区间
    //bool reverse=false;//false:小于rule[0]灭，大于rule[1]亮，true相反
    //---------------
    virtual vector<Operation> play(vector<AbstractMapUnit*>, int mapWidth, int mapHeight)=0;
};

#endif // ABSTRACTBOT_H
