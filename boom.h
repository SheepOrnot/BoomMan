#ifndef BOOM_H
#define BOOM_H
#include<QWidget>
#include"setting.h"
#include<QTimer>
#include<QObject>
#include<people.h>
class Boom :public QLabel
{
public:
    Boom(int XX,int YY,QWidget *parent);
    int Check(int XX,int YY,QWidget *parent);
    ~Boom();
    static int BaseX;
    static int BaseY;
    int X,Y;

protected:
    QPixmap Icon;//炸弹图标
    QPixmap Ruin;//炸弹特效
    int CountDown1;//爆装倒计时
    int CountDown2;//痕迹倒计时

    QTimer *Time2;
    QTimer *Time3;

    QVector<QLabel*> v;
};
class BoomA : public Boom
{
public:
    BoomA(int Lv,int XX,int YY,QWidget *parent);
    ~BoomA(){;}
    int R;
};

extern QVector<Boom*> BoomV;
#endif // BOOM_H
