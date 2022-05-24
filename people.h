#ifndef PEOPLE_H
#define PEOPLE_H
#include<QWidget>
#include<QTime>
#include<QString>
#include<QObject>
#include<QTimer>
#include<QApplication>
#include<QProcess>
#include"setting.h"
#include"tool.h"
#include "gameboard.h"
class people :public QLabel
{
public:
    people(int TYPE,int XX,int YY,QString NAME,QWidget *parent);
    people(const people& rhs);
    void Walk(int TYPE);//走路动画
    void SetPos(int TYPE);//静止时朝向
    void MovePos(int XX,int YY,int de);//改变坐标
    bool Check(int TYPE);
    void Reduceblood();
    bool CanBoom();

    QString name;//用户名
    QString Cname;//角色名
    int type;//类型
    int BoomMax;//可以同时放几个炸弹
    int BoomLength;//炸弹范围
    int speed;//人物速度
    QVector<QTime> BoomTime;//记录放置时间
    int BoomLv;//炸弹等级
    int BoomType;//炸弹类型 0 为默认炸弹
    int BoomRemain;//炸弹个数剩余
    int X,Y;//坐标
    int I;//动画第几帧
    int isAnimation;//动画状态
    int orientation;//人物朝向
    int deviation;//人物偏向
    int isWalk;//走路状态
    int blood;//血量

    QPixmap pixCha;//人物图像
    QPixmap pixRun;//人物跑步
    QTimer *Time1;
    QTimer *Time2;
    QTimer *Time3;

    static int BaseX;
    static int BaseY;

    enum Walk_Type{ Right = 1, Up, Left, Down };

    gameboard *GameBoard;


};

extern QSoundEffect *PickUp;
extern int GMode;
extern people *P1,*P2,*P3,*P4;
#endif // PEOPLE_H
