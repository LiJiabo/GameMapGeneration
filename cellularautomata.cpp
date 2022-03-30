#include "cellularautomata.h"

CellularAutomata::CellularAutomata()
{

}

CellularAutomata::CellularAutomata(int botNum,QString botName,int botPos[2]):AbstractBot(botNum,botName,botPos,CELLULARAUTOMATA)
{

}

vector<Operation> CellularAutomata::play(vector<AbstractMapUnit*> map, int mapWidth, int mapHeight)
{
    vector<Operation> operations;//暂时没用
    int directionArray[9][2]={{0,-1},
                              {1,-1},
                              {1,0},
                              {1,1},
                              {0,1},
                              {-1,1},
                              {-1,0},
                              {-1,-1},
                              {0,0}};
    int blackCount=0;
    for(int i=0;i<9;i++)
    {
        if(botPos[0]+directionArray[i][0]<0||botPos[0]+directionArray[i][0]>mapWidth-1||botPos[1]+directionArray[i][1]<0||botPos[1]+directionArray[i][1]>mapHeight-1)
            continue;//防止坐标越界
        if(map.at((botPos[0]+directionArray[i][0])*mapWidth+botPos[1])->getColor()==Qt::black)
            blackCount++;
    }
    if(blackCount>threshhold)
    {
        Operation op;
        op.pos[0]=botPos[0];
        op.pos[1]=botPos[1];
        op.cmd="lightUp";
        operations.push_back(op);
    }
    else if(blackCount==threshhold)
    {
        Operation op;
        op.pos[0]=botPos[0];
        op.pos[1]=botPos[1];
        op.cmd="maintain";
        operations.push_back(op);
    }
    else
    {
        Operation op;
        op.pos[0]=botPos[0];
        op.pos[1]=botPos[1];
        op.cmd="putOut";
        operations.push_back(op);
    }
    return operations;
}
