#include "play.h"

Play::Play(FormGame* formGame, QObject *parent) : QThread(parent)
{
    this->formGame=formGame;
}

void Play::run()
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
                    formgamedisplay->map.at(operation.pos[1]*(formGame->mapWidth)+operation.pos[0])->setColor(Qt::black);
                }
            }
        }
        //update
        formgamedisplay->update();
        QThread::sleep(1);
    }
}
