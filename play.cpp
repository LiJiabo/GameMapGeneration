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
                    formgamedisplay->map.at(operation.pos[1]*(formGame->mapWidth)+operation.pos[0])->setColor(Qt::white);
                }
                else if(operation.cmd=="maintain")
                {
                    ;
                }
                else if(operation.cmd=="putOut")
                {
                    formgamedisplay->map.at(operation.pos[1]*(formGame->mapWidth)+operation.pos[0])->setColor(Qt::black);//存在数据越界的问题
                    //原因：整个程序x、y不统一，需以一个标准统一一下！
                }
            }
        }
        //update
        formgamedisplay->update();
        detectWait();
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
