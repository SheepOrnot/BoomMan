#include "people.h"

int people::BaseX = 100 -48;
int people::BaseY = 50 -20 -48 -14;
people *P1 = NULL;
people *P2 = NULL;
people *P3 = NULL;
people *P4 = NULL;

people::people(int TYPE,int XX,int YY,QString NAME = "Unnamed",QWidget *parent = NULL)
{
    I = 0;
    X = XX;
    Y = YY;
    name = NAME;//用户名
    type = TYPE;//类型
    BoomMax = 1;//可以同时放几个炸弹
    BoomLength = 1;//炸弹范围
    speed = 50;//人物速度
    BoomTime.push_back(QTime(0,0));//记录放置时间
    BoomLv = 0;
    BoomType = 0;//炸弹类型 0 为默认炸弹
    BoomRemain = 0;//炸弹个数剩余
    isAnimation =0;
    Cname = "Alex";
    isWalk = 0;
    deviation = 0;
    blood = 1;

    /**///图像初始化
    QString str = QString(":/character/res\\character\\%1\\%2.png").arg(this->Cname).arg(this->Cname);
    pixCha = QPixmap(str); //右上左下
    if(!pixCha)
    {
        QMessageBox WR;
        WR.setText("Picture Cha Lose");
        WR.exec();
    }
    str = QString(":/character/res\\character\\%1\\%2_run.png").arg(this->Cname).arg(this->Cname);
    pixRun = QPixmap(str); //右上左下
    if(!pixRun)
    {
        QMessageBox WR;
        WR.setText("Picture Run Lose");
        WR.exec();
    }
    /**///
    this->setGeometry(0,0,48,68);
    this->SetPos(4);
    this->MovePos(X,Y);
    this->setParent(parent);
    Time1  = new QTimer(this);
    Time2  = new QTimer(this);
    Time3  = new QTimer(this);
    connect(Time1,&QTimer::timeout,[=](){
        if(I==0) this->setPixmap(pixRun.copy((isAnimation-1)*6*48+0*48,28,48,68));
        if(I==1) this->setPixmap(pixRun.copy((isAnimation-1)*6*48+1*48,28,48,68));
        if(I==2) this->setPixmap(pixRun.copy((isAnimation-1)*6*48+3*48,28,48,68));
        if(I==3) this->setPixmap(pixRun.copy((isAnimation-1)*6*48+4*48,28,48,68));
        int DatX = 0,DatY = 0;
        if(isAnimation == 1) DatX =  48/3/4*I;
        if(isAnimation == 2) DatY = -48/3/4*I;
        if(isAnimation == 3) DatX = -48/3/4*I;
        if(isAnimation == 4) DatY =  48/3/4*I;
        if(deviation == 1) DatX +=  48/3;
        if(deviation == 2) DatY += -48/3;
        if(deviation == 3) DatX += -48/3;
        if(deviation == 4) DatY +=  48/3;
        this->move(BaseX+X*48+DatX,BaseY+Y*48+DatY);
        orientation = isAnimation;
        I = I+1;
        if(I>3)
        {
            I = 0;
            Time1->stop();
            this->setPixmap(pixCha.copy(48*(isAnimation-1),28,48,68));
            if(isAnimation == deviation)
            {
                if(isAnimation == 1) ++X;
                if(isAnimation == 2) --Y;
                if(isAnimation == 3) --X;
                if(isAnimation == 4) ++Y;
                deviation = (deviation&1 ? 4-deviation : 6-deviation);

                if(Map[1][Y][X]>0)
                {
                    if(Map[1][Y][X]==1) ++blood;
                    if(Map[1][Y][X]==2) ++BoomLv;
                    for(QVector<Tool*>::iterator it = ToolV.begin(); it != ToolV.end(); ++it)
                    if((*it)->X == X&& (*it)->Y == Y)
                    {
                        (*it)->hide();
                        delete (*it);
                        std::iter_swap(it,ToolV.end()-1);
                        ToolV.pop_back();
                        break;
                    }
                    Map[1][Y][X] = 0;
                }
            }
            else if(deviation==0)
            {
                deviation = isAnimation;
            }
            else
            {
                deviation = 0;
            }
            DatX = DatY = 0;
            if(deviation == 1) DatX =  48/3;
            if(deviation == 2) DatY = -48/3;
            if(deviation == 3) DatX = -48/3;
            if(deviation == 4) DatY =  48/3;
            this->move(BaseX+X*48+DatX,BaseY+Y*48+DatY);
            isAnimation = 0;
            if(isWalk) Walk(isWalk);
        }
    });
    connect(Time2,&QTimer::timeout,[=](){
        Time2->stop();
        this->hide();
    });
    connect(Time3,&QTimer::timeout,[=](){
        Time3->stop();
        QString str = QString(":/character/res\\character\\%1\\%2.png").arg(this->Cname).arg(this->Cname);
        pixCha = QPixmap(str);
        str = QString(":/character/res\\character\\%1\\%2_run.png").arg(this->Cname).arg(this->Cname);
        pixRun = QPixmap(str);
        SetPos(orientation);
    });
}
//右上左下 1 2 3 4
bool people::Check(int TYPE)
{
    if((TYPE==1&& X>=15)||(TYPE==2&& Y<=1)||(TYPE==3&& X<=1)||(TYPE==4&& Y>=15)) return 0;//判边界
    if(TYPE==1&&Map[0][Y][X+1]>0) return 0;
    if(TYPE==2&&Map[0][Y-1][X]>0) return 0;
    if(TYPE==3&&Map[0][Y][X-1]>0) return 0;
    if(TYPE==4&&Map[0][Y+1][X]>0) return 0;
    return 1;
}

void people::Walk(int TYPE)
{
    if(blood<=0) return;
    if(isAnimation) return;
    if(TYPE>4||TYPE<1) return;
    SetPos(TYPE);
    if(deviation==0||abs(TYPE-deviation)!=2)
    {
        if((TYPE==1&& X>=15)||(TYPE==2&& Y<=1)||(TYPE==3&& X<=1)||(TYPE==4&& Y>=15)) return;//判边界
        if(TYPE==1&&Map[0][Y][X+1]>0) return;
        if(TYPE==2&&Map[0][Y-1][X]>0) return;
        if(TYPE==3&&Map[0][Y][X-1]>0) return;
        if(TYPE==4&&Map[0][Y+1][X]>0) return;
    }
    if(deviation==0||TYPE==deviation||abs(TYPE-deviation)==2)
    {
        isAnimation = TYPE;
    }
    else
    {
//        isAnimation = (deviation&1 ? 4-deviation : 6-deviation);
        this->move(BaseX+X*48,BaseY+Y*48);
        this->setPixmap(pixCha.copy(48*(TYPE-1),28,48,68));
        deviation = 0;
        isAnimation = TYPE;
    }
    isWalk = TYPE;
    I = 0;
    Time1->start(this->speed);
}

void people::MovePos(int XX,int YY)
{
    if(blood<=0) return;
    if(isAnimation) return;
    if(XX<1||XX>15||YY<1||YY>15) return;
    this->move(BaseX+X*48,BaseY+Y*48);
}

void people::SetPos(int TYPE)
{
    if(isAnimation) return;
    if(TYPE>4||TYPE<1) return;
    this->setPixmap(pixCha.copy(48*(TYPE-1),28,48,68));
    orientation = TYPE;
}

void people::Reduceblood()
{
    this->raise();
    --blood;
    QString str = QString(":/character/res\\character\\%1\\%2_Died.png").arg(this->Cname).arg(this->Cname);
    pixCha = QPixmap(str);
    str = QString(":/character/res\\character\\%1\\%2_run_Died.png").arg(this->Cname).arg(this->Cname);
    pixRun = QPixmap(str);
    if(blood > 0)
    {
        Time3->start(500);
        SetPos(orientation);
        return;
    }
    Time1->stop();
    this->setPixmap(pixCha.copy(48*(orientation-1),28,48,68));
    Time2->start(1300);
//    QMessageBox WR;
//    WR.setText(name+QString(" Lose"));
//    WR.exec();
}

bool people::CanBoom()
{
    if(blood<=0) return 0;
    if(Map[0][Y][X]>0) return 0;
    if(BoomTime.front().secsTo(QTime::currentTime())<8) return 0;
    BoomTime.pop_front();
    BoomTime.push_back(QTime::currentTime());
    return 1;
}

people::people(const people& rhs) :
    name(rhs.name),
    type(rhs.type),
    X(rhs.X),
    Y(rhs.Y)
{

}
