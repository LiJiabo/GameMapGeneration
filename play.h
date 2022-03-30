#ifndef PLAY_H
#define PLAY_H

#include <QThread>
#include <atomic>
#include <QMutex>
#include <QWaitCondition>
#include <abstractbot.h>
#include "mainwindow.h"
#include "formgamedisplay.h"
using namespace std;

class FormGame;

class Play : public QThread
{
public:
    explicit Play(FormGame* formGame, QObject *parent = nullptr);
    void run();
    int turn=0;
    int turnLimit=100;//turn<=turnLimit
    enum State{STOPPED, RUNNING, PAUSED};
    State getState() const;
    void pause();
    void resume();
private:
    FormGame* formGame=nullptr;
    atomic_bool pauseFlag=false;
    QMutex mutex;
    QWaitCondition condition;
    void detectWait();
};

#endif // PLAY_H
