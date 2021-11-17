#ifndef DIALOGNEWBOTS_H
#define DIALOGNEWBOTS_H

#include <QDialog>

namespace Ui {
class DialogNewBots;
}

class DialogNewBots : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewBots(int botNum, QWidget *parent = nullptr);
    ~DialogNewBots();

private:
    Ui::DialogNewBots *ui;

signals:
    void windowClose();
    void windowSuccess();

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonOK_clicked();
};

#endif // DIALOGNEWBOTS_H
