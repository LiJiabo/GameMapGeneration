#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <iostream>
#include <dialognewgame.h>
#include <formgame.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FormGame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DialogNewGame* dialognewgame;
    FormGame* formgame=nullptr;
private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent*);
};
#endif // MAINWINDOW_H
