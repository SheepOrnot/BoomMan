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

    int ready_cli = 0;
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
    void cliReady();
    void connectOk();
    void newConnect();
    void gamestart_gp(dataPack p);
    void gamestart();

    void on_pe1v1_clicked();
    void on_pp1v1_clicked();
    void on_ppee2v2_clicked();

    void on_Alex_clicked();
    void on_Alex_2_clicked();
    void on_Dan_clicked();
    void on_Dan_2_clicked();
    void on_Molly_clicked();
    void on_Molly_2_clicked();
    void on_Roki_clicked();
    void on_Roki_2_clicked();

    void on_start_clicked();
    void on_back_clicked();
    void on_CreateSvr_clicked();
    void on_JoinSvr_clicked();

signals:
    void callClose();
};

#endif // GAMEPARA_H
