#ifndef GAMEPARA_H
#define GAMEPARA_H

#include <QWidget>
#include "gamewidget.h"

namespace Ui {
class gamepara;
}

class gamepara : public QWidget
{
    Q_OBJECT

public:
    explicit gamepara(QWidget *parent = nullptr, int svrType = 0);
    ~gamepara();

    GameWidget *game;

    int gamemode = 2;
    int pSel1 = 0, pSel2 = 0, pSel3 = 0, pSel4 = 0;

    void checkP1();
    void checkP2();
    void checkAI_1();
    void checkAI_2();
    void hideP1();
    void hideP2();

private:
    Ui::gamepara *ui;
};

#endif // GAMEPARA_H
