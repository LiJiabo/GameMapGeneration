#ifndef DIALOGBOTSETTINGS_H
#define DIALOGBOTSETTINGS_H

#include <QDialog>

namespace Ui {
class DialogBotSettings;
}

class DialogBotSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBotSettings(QWidget *parent = nullptr);
    ~DialogBotSettings();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DialogBotSettings *ui;
signals:
    void windowClose();
    void windowSuccess();
};

#endif // DIALOGBOTSETTINGS_H
