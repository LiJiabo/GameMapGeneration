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

    void on_comboBoxBotType_currentTextChanged(const QString &arg1);

private:
    Ui::DialogNewGame *ui;

signals:
    void windowClose();
    void formGameOpen(int mapWidth,int mapHeight);
};

#endif // DIALOGNEWGAME_H
