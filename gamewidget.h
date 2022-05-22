#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include"setting.h"
#include "people.h"
#include "boom.h"
#include "AI.h"
#include "server.h"
#include "client.h"
#include <random>
namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    int svrType;
    bool playerCheck(people* p);
    void hasMoved(int move, int player);

    explicit GameWidget(QWidget *parent = nullptr, int svrType = 0, int pSel1 = 0, int pSel2 = 0, int pSel3 = 0, int pSel4 = 0, int gamemode = 1, int mapseed = 0);
    ~GameWidget();

private:
    Ui::GameWidget *ui;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    //void updateClient(dataPack p);


signals:
    void hasMovedSignal(dataPack p);

};

extern GameWidget game;
#endif // GAMEWIDGET_H
