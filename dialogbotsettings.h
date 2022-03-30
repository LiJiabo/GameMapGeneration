#ifndef DIALOGBOTSETTINGS_H
#define DIALOGBOTSETTINGS_H

#include <QDialog>
#include <abstractbot.h>

namespace Ui {
class DialogBotSettings;
}

class DialogBotSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBotSettings(int mapWidth, int mapHeight, vector<AbstractBot*> bots, QWidget *parent = nullptr);
    ~DialogBotSettings();
    int mapWidth=0,mapHeight=0;
     vector<AbstractBot*> bots;

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::DialogBotSettings *ui;
signals:
    void windowClose();
    void windowSuccess();
};

#endif // DIALOGBOTSETTINGS_H
