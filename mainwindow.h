#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <dialognewgame.h>
#include <formgame.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DialogNewGame* dialognewgame;
    FormGame* formgame;
private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent*);
};
#endif // MAINWINDOW_H
