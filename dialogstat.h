#ifndef DIALOGSTAT_H
#define DIALOGSTAT_H

#include <QDialog>

namespace Ui {
class DialogStat;
}

class DialogStat : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStat(QWidget *parent = nullptr);
    ~DialogStat();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::DialogStat *ui;

signals:
    void windowClose();
};

#endif // DIALOGSTAT_H
