#include "boom.h"
QVector<Boom*> BoomV;
int Boom::BaseX = 215 -48;
int Boom::BaseY = 34 -48;
int BoomA::Check(int XX,int YY,QWidget *parent)
{
    if(XX<1||XX>15||YY<1||YY>15||Map[0][YY][XX]>1) return 2;
    QString str = QString(":/boom/res\\boom\\boomA_Flame.png");
    QPixmap pix = QPixmap(str);
    QLabel *LA = new QLabel;
    LA->setGeometry(0,0,48,48);
    LA->move(BaseX+XX*48,BaseY+YY*48);
    LA->setParent(parent);
    LA->setPixmap(QPixmap(str));
    LA->show();
    v.push_back(LA);

    if(Map[1][YY][XX]>0&&Map[0][YY][XX]==1)
    {
        ToolV.push_back(new Tool(Map[1][YY][XX],XX,YY,parent));
        if(P1!=NULL)P1->raise();
        if(P2!=NULL)P2->raise();
        if(P3!=NULL)P3->raise();
        if(P4!=NULL)P4->raise();
    }
    else if(Map[1][YY][XX]>0)
    {
        Map[1][YY][XX]=0;
        for(QVector<Tool*>::iterator it = ToolV.begin(); it != ToolV.end(); ++it)
        if((*it)->X == XX&& (*it)->Y == YY)
        {
            (*it)->hide();
            delete (*it);
            std::iter_swap(it,ToolV.end()-1);
            ToolV.pop_back();
            break;
        }
    }

    if(P1!=NULL&&P1->X==XX&&P1->Y==YY) P1->Reduceblood();
    if(P2!=NULL&&P2->X==XX&&P2->Y==YY) P2->Reduceblood();
    if(P3!=NULL&&P3->X==XX&&P3->Y==YY) P3->Reduceblood();
    if(P4!=NULL&&P4->X==XX&&P4->Y==YY) P4->Reduceblood();
    if(Map[0][YY][XX] == 1) {Map[0][YY][XX]=0;Build[YY][XX]->hide(); return 1;}
    return 0;
}
Boom::Boom(int XX,int YY,QWidget *parent)
{
    fa = parent;
    X = XX, Y = YY;
    CountDown1 = 4000;
    CountDown2 = 300;
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
    this->setPixmap(QPixmap(str)); //????????????
    this->show();
    Map[0][Y][X] = 2;

    soundThread *sound = new soundThread;

    connect(Time2,&QTimer::timeout,[=](){
        //if(X == 10 && Y == 1) return;
        sound->setType(soundThread::boom);
        sound->start();
        sound->wait();
        Time2->stop();
        this->hide();
        Map[0][Y][X] = 0;
        Check(X,Y,fa);
        for(int i = 1; i <= R && !Check(X+i,Y,fa); ++i);
        for(int i = 1; i <= R && !Check(X-i,Y,fa); ++i);
        for(int i = 1; i <= R && !Check(X,Y+i,fa); ++i);
        for(int i = 1; i <= R && !Check(X,Y-i,fa); ++i);
        Time3->start(CountDown2);
    });
    connect(Time3,&QTimer::timeout,[=](){
        //if(X == 10 && Y == 1) return;
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
