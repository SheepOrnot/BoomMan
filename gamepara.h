#ifndef GAMEPARA_H
#define GAMEPARA_H

#include <QMainWindow>
#include <QGraphicsOpacityEffect>
#include <QMovie>
#include <QFile>
#include "gamewidget.h"
#include "setting.h"
#include "server.h"
#include "client.h"

namespace Ui {
class gamepara;
}

class gamepara : public QMainWindow
{
    Q_OBJECT

public:
    explicit gamepara(QWidget *parent = nullptr, int _svrType = 0);
    ~gamepara();

    GameWidget *game;
    QWidget *fa = nullptr;
    QTimer *overtime;
    QLabel *m_background;
    QMovie *backgroundMovie;
    QFile *IPfile;
    char IP[20];

    int gamemode = -1;
    int pSel1 = -1, pSel2 = -1, pSel3 = -1, pSel4 = -1;
    int mapseed;

    int connectNum = 0;

    int svrType = 0;

    void checkP1();
    void checkP2();
    void checkAI_1();
    void checkAI_2();
    void hideP1();
    void hideP2();
    void showAll();
    void waitSvrConnect();
    void waitSvrStart();
    bool checkIP(QString ip);

private:
    Ui::gamepara *ui;

public slots:
    void cliSel(dataPack p);
    void connectOk();
    void newConnect();
    void gamestart_gp(dataPack p);
    void gamestart();

signals:
    void callClose();
};

#endif // GAMEPARA_H
