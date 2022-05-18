#include "gameboard.h"

int gameboard::BaseX = 8;
int gameboard::BaseY = 34;
int ci = 0;
gameboard::gameboard(int TYPE,QString NAME = "Unnamed",QWidget *parent = NULL)
{
    NumHeart = NumBoom = 1;
    NumSpeed = NumPower = 0;
    name = NAME;
    if(TYPE==0) Cname = "Alex";
    if(TYPE==1) Cname = "Dan";
    if(TYPE==2) Cname = "Molly";
    if(TYPE==3) Cname = "Roki";
    QString str = QString(":/character/res\\character\\%1\\%2.png").arg(this->Cname).arg(this->Cname);
    QPixmap pix = QPixmap(str);
    Cha.setGeometry(0,0,48,68);
    Cha.setPixmap(pix.copy(48*3,28,48,68));
    Cha.setParent(this);
    Cha.move(5,5+10);
//    Nam.setGeometry(0,0,48,30);
    Nam.setText(name);
    Nam.setStyleSheet("font-size:32px");
    Nam.move(13,68+5+10);
    Nam.setParent(this);
    str = QString(":/tool/res\\tool\\PlayerHeart.png");
    pix = QPixmap(str);
    Heart.setGeometry(0,0,22,22);
    Heart.setPixmap(pix);
    Heart.move(58,10);
    Heart.setParent(this);
    str = QString(":/tool/res\\tool\\PlayerSpeed.png");
    pix = QPixmap(str);
    Speed.setGeometry(0,0,22,22);
    Speed.setPixmap(pix);
    Speed.move(58,40);
    Speed.setParent(this);
    str = QString(":/tool/res\\tool\\PlayerBoom.png");
    pix = QPixmap(str);
    Boom.setGeometry(0,0,22,22);
    Boom.setPixmap(pix);
    Boom.move(58,70);
    Boom.setParent(this);
    str = QString(":/tool/res\\tool\\PlayerPower.png");
    pix = QPixmap(str);
    Power.setGeometry(0,0,22,22);
    Power.setPixmap(pix);
    Power.move(58,100);
    Power.setParent(this);

    HeartN.setGeometry(0,0,44,22);
    HeartN.setParent(this);
    HeartN.move(180,10);
    HeartN.setText(QString::number(NumHeart));
    HeartN.setStyleSheet("font-size:22px");
    SpeedN.setGeometry(0,0,44,22);
    SpeedN.setParent(this);
    SpeedN.move(180,40);
    SpeedN.setText(QString::number(NumSpeed));
    SpeedN.setStyleSheet("font-size:22px");
    BoomN.setGeometry(0,0,44,22);
    BoomN.setParent(this);
    BoomN.move(180,70);
    BoomN.setText(QString::number(NumBoom));
    BoomN.setStyleSheet("font-size:22px");
    PowerN.setGeometry(0,0,44,22);
    PowerN.setParent(this);
    PowerN.move(180,100);
    PowerN.setText(QString::number(NumPower));
    PowerN.setStyleSheet("font-size:22px");
    Y = ++ci;
    this->setFixedSize(200,130);
    this->setParent(parent);
    this->move(BaseX,BaseY+(Y-1)*150);

    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color:rgb(215,215,215)");
}
void gameboard::Set(int NH = 1,int NS = 40,int NB = 1,int NP = 0)
{
    NumHeart = NH;
    NumSpeed = (40-NS)/5;
    NumBoom = NB;
    NumPower = NP;

    HeartN.setText(QString::number(NumHeart));
    SpeedN.setText(QString::number(NumSpeed));
    BoomN.setText(QString::number(NumBoom));
    PowerN.setText(QString::number(NumPower));
}
