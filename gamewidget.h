#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include"setting.h"
#include "people.h"
#include "boom.h"
#include "AI.h"
#include "netplayer.h"
#include "server.h"
#include "client.h"
namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    QTimer *AITime;
    static int AISpeed;
    int AIComputing;
    Server* svr;
    Client* cli;
    int svrType;

    explicit GameWidget(QWidget *parent = nullptr, int svrType = 0);
    ~GameWidget();

private:
    Ui::GameWidget *ui;

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public slots:
    void updateClient(dataPack p);


signals:
    void hasMoved(int move, int player);

};

extern GameWidget game;
#endif // GAMEWIDGET_H
