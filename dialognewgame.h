#ifndef DIALOGNEWGAME_H
#define DIALOGNEWGAME_H

#include <QDialog>
#include <QString>

namespace Ui {
class DialogNewGame;
}

class DialogNewGame : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewGame(QWidget *parent = nullptr);
    ~DialogNewGame();

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonOK_clicked();

private:
    Ui::DialogNewGame *ui;

signals:
    void windowClose();
    void formGameOpen(int mapWidth,int mapHeight,int botNum, int threshold);
};

#endif // DIALOGNEWGAME_H
