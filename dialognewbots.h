#ifndef DIALOGNEWBOTS_H
#define DIALOGNEWBOTS_H

#include <QDialog>
#include "abstractbot.h"

namespace Ui {
class DialogNewBots;
}

class DialogNewBots : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewBots(int botNum, int mapWidth, int mapHeight, vector<vector<bool>>* selected, QWidget *parent = nullptr);
    ~DialogNewBots();
    int mapWidth=0,mapHeight=0;
    QStringList builtinBotTypes={"CellularAutomata"};

private:
    Ui::DialogNewBots *ui;
    QWidget* dynamicWidget;

signals:
    void windowClose();
    void windowSuccess(int botNum,QString botName,int botPos[2],BotType botType);

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonOK_clicked();
    void on_comboBoxBotCreateType_currentTextChanged(const QString &arg1);
    void on_tableWidget_currentCellChanged(int currentRow, int currentColumn, int, int);
};

#endif // DIALOGNEWBOTS_H
