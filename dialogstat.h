#ifndef DIALOGSTAT_H
#define DIALOGSTAT_H

#include <QDialog>

namespace Ui {
class DialogStat;
}

class FormGame;

class DialogStat : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStat(FormGame* formGame, QWidget *parent = nullptr);
    ~DialogStat();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonSmooth_clicked();

    void on_pushButtonLog_clicked();

    void on_pushButtonTrain_clicked();

private:
    Ui::DialogStat *ui;
    FormGame* formGame=nullptr;
    int white, black;
    double balance;
    int smooth=-1;//-1表示没有计算

signals:
    void windowClose();
};

#endif // DIALOGSTAT_H
