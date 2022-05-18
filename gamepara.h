#ifndef GAMEPARA_H
#define GAMEPARA_H

#include <QMainWindow>
#include <QGraphicsOpacityEffect>
#include "gamewidget.h"

namespace Ui {
class gamepara;
}

class gamepara : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamepara(QWidget *parent = nullptr, int svrType = 0);
    ~gamepara();

    GameWidget *game;

    int gamemode = -1;
    int pSel1 = -1, pSel2 = -1, pSel3 = -1, pSel4 = -1;

    void checkP1();
    void checkP2();
    void checkAI_1();
    void checkAI_2();
    void hideP1();
    void hideP2();
    void showAll();

private:
    Ui::gamepara *ui;
};

#endif // GAMEPARA_H
