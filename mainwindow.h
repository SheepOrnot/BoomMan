#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"gamepara.h"
#include"setting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    gamepara *para;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:


};
#endif // MAINWINDOW_H
