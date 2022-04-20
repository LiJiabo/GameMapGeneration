#include "play.h"

Play::Play(FormGame* formGame, QObject *parent) : QThread(parent)
{
    this->formGame=formGame;
}

void Play::run()//下一步任务：参照阅读列表中CSDN那篇文章实现暂停功能
{
    for(;turn<=turnLimit;turn++)
    {
        vector<AbstractBot*>& bots=formGame->getBots();
        FormGameDisplay* formgamedisplay=formGame->getFormGameDisplay();
        for(AbstractBot* botP:bots)
        {
            vector<Operation> operations(botP->play(formgamedisplay->map,formGame->mapWidth,formGame->mapHeight));
            //parse
            for(Operation& operation:operations)
            {
                if(operation.cmd=="lightUp")
                {
                    formgamedisplay->map.at(operation.pos[0]*(formGame->mapWidth)+operation.pos[1])->setColor(Qt::white);//不能变，因为统计亮暗点个数是直接和white比较的
                }//而且formgamedisplay.cpp里面也是靠判断Qt::black来转换地图的
                else if(operation.cmd=="maintain")
                {
                    ;
                }
                else if(operation.cmd=="putOut")
                {
                    formgamedisplay->map.at(operation.pos[0]*(formGame->mapWidth)+operation.pos[1])->setColor(Qt::black);
                }
            }
        }
        //update
        formgamedisplay->update();
        QThread::sleep(1);
        detectWait();
    }
}

Play::State Play::getState() const
{
    if(!this->isRunning())
        return STOPPED;
    else if((this->isRunning())&&pauseFlag)
        return PAUSED;
    else
        return RUNNING;
}

void Play::pause()
{
    if(this->isRunning())
        pauseFlag=true;
}

void Play::resume()
{
    if(this->isRunning())
    {
        pauseFlag=false;
        condition.wakeAll();
    }
}

void Play::detectWait()
{
    if(pauseFlag)
    {
        mutex.lock();
        condition.wait(&mutex);
        mutex.unlock();
    }
}
