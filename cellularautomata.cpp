#include "cellularautomata.h"

CellularAutomata::CellularAutomata()
{

}

CellularAutomata::CellularAutomata(int botNum,string botName,int botPos[2],BotType botType):AbstractBot(botNum,botName,botPos,botType)
{

}

vector<Operation> CellularAutomata::play(int next)
{
    Operation a;  // 中间变量
    a.pos[0]=botPos[0];
    a.pos[1]=botPos[1];

if(next>3) {
    a.cmd="light";
    back.push_back(a);
}
    if (next==3)
    {
       a.cmd="extinguish";
       back.push_back(a);
    }
    if (next<3)
    {
       a.cmd="unchanged";
       back.push_back(a);
    }
    return back;
}
void light(vector<Operation> back){
if(back[0].cmd=="light"){

}
}

