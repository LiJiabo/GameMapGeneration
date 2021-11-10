#include<all.h>
#include<QDebug>
vector<Operation> bot_state;
void initialize(int x,int y){
    bot_state.resize(x*y);
  int n=0;
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++)
        {
            bot_state[n].pos[0]=i;
            bot_state[n].pos[1]=j;
            bot_state[n].cmd="black";
            n++;
        }
    }
    //for(int i=0;i<x*y;i++)
    //   qDebug()<<bot_state[i].pos[0]<<bot_state[i].pos[1];
    //qDebug()<<"\n";
}
