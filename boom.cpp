#include "boom.h"
QVector<Boom*> BoomV;
int Boom::BaseX = 100 -48;
int Boom::BaseY = 50 -48;
int Boom::Check(int XX,int YY,QWidget *parent)
{
    if(XX<1||XX>15||YY<1||YY>15||Map[0][YY][XX]>1) return 2;
    QString str = QString(":/boom/res\\boom\\boomA_1.png");
    QPixmap pix = QPixmap(str);
    QLabel *LA = new QLabel;
    LA->setGeometry(0,0,48,48);
    LA->move(BaseX+XX*48,BaseY+YY*48);
    LA->setParent(parent);
    LA->setPixmap(QPixmap(str));
    LA->show();
    v.push_back(LA);
    if(P1->X==XX&&P1->Y==YY) P1->Reduceblood();
    if(P2->X==XX&&P2->Y==YY) P2->Reduceblood();
//    if(P3->X==XX&&P3->Y==YY) P3->Reduceblood();
//    if(P4->X==XX&&P4->Y==YY) P4->Reduceblood();
    if(Map[0][YY][XX] == 1) {Map[0][YY][XX]=0;Build[YY][XX]->hide(); return 1;}
    return 0;
}
Boom::Boom(int XX,int YY,QWidget *parent)
{
    X = XX, Y = YY;
    CountDown1 = 4000;
    CountDown2 = 70;
    Time2 = new QTimer(this);
    Time3 = new QTimer(this);
    this->setGeometry(0,0,48,48);
    this->move(BaseX+X*48,BaseY+Y*48);
    this->setParent(parent);
}

BoomA::BoomA(int Lv,int XX,int YY,QWidget *parent):Boom(XX,YY,parent)
{
    R = 1+Lv;
    QString str = QString(":/boom/res\\boom\\boomA_1.png");
    QPixmap pix = QPixmap(str);
    if(!pix)
    {
        QMessageBox WR;
        WR.setText("Picture BoomA Lose");
        WR.exec();
    }
    this->setPixmap(QPixmap(str)); //右上左下
    this->show();
    Map[0][Y][X] = 2;
    connect(Time2,&QTimer::timeout,[=](){
        Time2->stop();
        this->hide();
        Map[0][Y][X] = 0;
        Check(X,Y,parent);
        for(int i = 1; i <= R && !Check(X+i,Y,parent); ++i);
        for(int i = 1; i <= R && !Check(X-i,Y,parent); ++i);
        for(int i = 1; i <= R && !Check(X,Y+i,parent); ++i);
        for(int i = 1; i <= R && !Check(X,Y-i,parent); ++i);
        Time3->start(CountDown2);
    });
    connect(Time3,&QTimer::timeout,[=](){
        Time3->stop();
        while(!v.empty())
        {
            v.back()->hide();
            delete v.back();
            v.pop_back();
        }
        for(QVector<Boom*>::iterator it = BoomV.begin(); it != BoomV.end(); ++it)
        if((*it)->X == X&& (*it)->Y == Y)
        {
            std::iter_swap(it,BoomV.end()-1);
            BoomV.pop_back();
            break;
        }
        delete this;
    });

    Time2->start(CountDown1);
}

Boom::~Boom()
{
    delete Time2;
    delete Time3;
    while(!v.empty())
    {
        delete v.back();
        v.pop_back();
    }
}
