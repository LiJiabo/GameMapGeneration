#include "abstractbot.h"

AbstractBot::AbstractBot()
{

}

AbstractBot::AbstractBot(int botNum,QString botName,int botPos[2],BotType botType)
{
    this->botNum=botNum;
    this->botName=botName;
    this->botPos[0]=botPos[0];
    this->botPos[1]=botPos[1];
    this->botType=botType;
}
