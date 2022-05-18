#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include"setting.h"

class gameboard : public QWidget
{
public:
    gameboard(int TYPE,QString NAME,QWidget *parent);
    void Set(int NH,int NS,int NB,int NP);
    int Y;
    QString name;//用户名
    QString Cname;//角色名
    QLabel Cha;
    QLabel Nam;
    QLabel Heart;
    QLabel Speed;
    QLabel Boom;
    QLabel Power;
    int NumHeart;
    int NumSpeed;
    int NumBoom;
    int NumPower;
    QLabel HeartN;
    QLabel SpeedN;
    QLabel BoomN;
    QLabel PowerN;
    static int BaseX;
    static int BaseY;
};

extern int ci;
#endif // GAMEBOARD_H
