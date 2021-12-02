#ifndef PLAY_H
#define PLAY_H

#include <QThread>
#include <abstractbot.h>
#include "mainwindow.h"
#include "formgamedisplay.h"

class FormGame;

class Play : public QThread
{
public:
    explicit Play(FormGame* formGame, QObject *parent = nullptr);
    void run();
    int turn=0;
    int turnLimit=100;//turn<=turnLimit
private:
    FormGame* formGame=nullptr;
};

#endif // PLAY_H
