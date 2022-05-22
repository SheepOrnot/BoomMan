#include "gamewidget.h"
#include "ui_gamewidget.h"

extern int GsvrType = 0;

inline int Rand(int x)
{
    return rand()%x+1;
}

bool Checkmap(int x,int y)
{
    if(Map[0][x][y]) return 0;
    if((x==1||x==15)&&(y==1||y==15)) return 0;
    if((y==1&&x==2)||(x==2&&y==2)) return 0;
    if((x==14&&y==1)||(x==15&&y==2)) return 0;
    if((x==15&&y==14)||(x==14&&y==15)) return 0;
    if((y==14&&x==1)||(y==14&&x==2)) return 0;
    return 1;
}

GameWidget::GameWidget(QWidget *parent, int _svrType, int pSel1, int pSel2, int pSel3, int pSel4, int gamemode, int mapseed) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    this->setFixedSize(960,790);

    qDebug() << "GW:checkpoint1";

    QPixmap icon(":/boom/res\\boom\\boomA_1.png");

    this->setWindowTitle("炸弹人");
    this->setWindowIcon(icon);

    GMode = gamemode;
    GsvrType = _svrType;

    srand(mapseed);

    int ITEM[6];
    ITEM[1] = 15;
    ITEM[2] = 10;
    ITEM[3] = 10;
    ITEM[4] = 10;
    for(int x,y,u = 100; u; --u)
    {
        do
        {
            x = Rand(16),y = Rand(16);
        }
        while(!Checkmap(x,y));
        Map[0][x][y] = 1;
        for(int i = 1; i <= 4; ++i)
            if(ITEM[i])
            {
                ITEM[i]--;
                Map[1][x][y] = i;
                break;
            }
    }

    for(int i=1;i<16;i++)
    {
        for(int j=1;j<16;j++)
        {
            //绘制背景图片
            QPixmap pix = QPixmap(":/floor/res\\floor\\normalFloor2.png");
            if(!pix)
            {
                QMessageBox::information(this, "error!", "Pixmap Open Fail!");
                return;
            }
            QLabel *label=new QLabel;
            label->setGeometry(0,0,48,48);
            label->setPixmap(pix);
            label->setParent(this);
            label->move(215+(j-1)*48,34+(i-1)*48);

        }
    }


    for(int i=1;i<16;i++)
    {
        for(int j=1;j<16;j++)
        {
            Build[i][j] = new QLabel;
            if(!Map[0][i][j]) continue;
            if((i>=7&&i<=9)&&(j>=7&&j<=9)) continue;
            //绘制图片
            QPixmap pix;
            if(Map[0][i][j]==1)
            pix = QPixmap(":/floor/res\\floor\\item1.png");
            else pix = QPixmap(":/floor/res\\floor\\wall1.png");
            if(!pix)
            {
                QMessageBox::information(this, "error!", "Pixmap Open Fail!");
                return;
            }
            Build[i][j]->setGeometry(0,0,48,48);
            Build[i][j]->setPixmap(pix);
            Build[i][j]->setParent(this);
            Build[i][j]->move(215+(j-1)*48,34+(i-1)*48);

        }
    }

    QPixmap pix = QPixmap(":/floor/res\\floor\\centre1.png");
    if(!pix)
    {
        QMessageBox::information(this, "error!", "Pixmap Open Fail!");
        return;
    }
    QLabel *Centre = new QLabel;
    Centre->setGeometry(0,0,48*3,48*3);
    Centre->setPixmap(pix);
    Centre->setParent(this);
    Centre->move(215+(7-1)*48,34+(7-1)*48);

    qDebug() << "GW:checkpoint2";

    svrType = _svrType;
    if(gamemode == 1)
    {
        P1 = new people(pSel1,1,1,"P1",this);
        P2 = new people(pSel2,15,15,"P2",this);

        //是否开启服务器
        if (svrType == 1)
        {
            qDebug() << "open server" << endl;

            cli->fa = this;
            //connect(this, SIGNAL(hasMoved(int, int)), cli, SLOT(slotSend(int, int)));               //发送数据到服务器
            //connect(cli, SIGNAL(moveNetPlayer(dataPack)), this, SLOT(updateClient(dataPack)));      //本地移动
        }
        //开启一个客户端
        else if (svrType == 2)
        {
            qDebug() << "open client" << endl;

            cli->fa = this;
            //connect(this, SIGNAL(hasMoved(int, int)), cli, SLOT(slotSend(int, int)));               //发送数据到服务器
            //connect(cli, SIGNAL(moveNetPlayer(dataPack)), this, SLOT(updateClient(dataPack)));      //本地移动
        }

    }
    else if(gamemode == 2)
    {
        P1 = new people(pSel1,1,1,"P1",this);
        P2 = new people(pSel2,15,15,"P2",this);
    }
    else if(gamemode == 3)
    {
        P1 = new people(pSel1,1,1,"P1",this);
        P3 = new AIPlayer(pSel3,15,15,"AI",this);
    }
    else if(gamemode == 4)
    {
        P1 = new people(pSel1,1,1,"P1",this);
        P2 = new people(pSel2,15,1,"P2",this);
        P3 = new AIPlayer(pSel3,1,15,"A1",this);
        P4 = new AIPlayer(pSel4,15,15,"A2",this);
    }

    qDebug() << "GW:checkpoint3";

}

bool GameWidget::playerCheck(people* p)
{
    if(GMode==0) return 0;
    if(p->blood<=0) return 0;
    if(p->isAnimation) return 0;
    return 1;
}

void GameWidget::hasMoved(int move, int player)
{
    dataPack p;
    p.move = move;
    p.player = player;
    cli->slotSend(p);
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{
    //    if(event->isAutoRepeat()) return;
    switch (event->key())
    {
    case Qt::Key_Escape:
        qDebug() << "Escape";
        break;
    case Qt::Key_D:
        qDebug() << "D";
        if (svrType) {if(svrType == 1 && playerCheck(P1)) hasMoved(1, 1);}
        else if(P1!=NULL)P1->Walk(1);
        break;
    case Qt::Key_W:
        qDebug() << "W";
        if (svrType) {if(svrType == 1 && playerCheck(P1)) hasMoved(2, 1);}
        else if(P1!=NULL)P1->Walk(2);
        break;
    case Qt::Key_A:
        qDebug() << "A";
        if (svrType) {if(svrType == 1 && playerCheck(P1)) hasMoved(3, 1);}
        else if(P1!=NULL)P1->Walk(3);
        break;
    case Qt::Key_S:
        qDebug() << "S";
        if (svrType) {if(svrType == 1 && playerCheck(P1)) hasMoved(4, 1);}
        else if(P1!=NULL)P1->Walk(4);
        break;
    case Qt::Key_Space:
        qDebug() << "Space";
        if (P1!=NULL&&P1->CanBoom())
        {
            if (svrType) {if(svrType == 1) hasMoved(5, 1);}
            else
            {
                BoomV.push_back(new BoomA(P1->BoomLv, P1->X, P1->Y, this));
                P1->raise();
            }
        }
        break;
    case Qt::Key_Right:
        qDebug() << "Right";
        if (svrType) { if(svrType == 2 && playerCheck(P2)) hasMoved(1, 2); }
        else if(P2!=NULL)P2->Walk(1);
        break;
    case Qt::Key_Up:
        qDebug() << "Up";
        if (svrType) { if(svrType == 2 && playerCheck(P2)) hasMoved(2, 2); }
        else if(P2!=NULL)P2->Walk(2);
        break;
    case Qt::Key_Left:
        qDebug() << "Left";
        if (svrType) { if(svrType == 2 && playerCheck(P2)) hasMoved(3, 2); }
        else if(P2!=NULL)P2->Walk(3);
        break;
    case Qt::Key_Down:
        qDebug() << "Down";
        if (svrType) { if(svrType == 2 && playerCheck(P2)) hasMoved(4, 2); }
        else if(P2!=NULL)P2->Walk(4);
        break;
    case Qt::Key_Enter:
        qDebug() << "Enter";
        if (P2!=NULL&&P2->CanBoom())
            if (svrType) {if(svrType == 2) hasMoved(5, 2);}
            else
            {
                BoomV.push_back(new BoomA(P2->BoomLv, P2->X, P2->Y, this));
                P2->raise();
            }
        break;
    }
}
void GameWidget::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat()) return;
    switch(event->key())
    {
    case Qt::Key_D:
       qDebug()<<"R_D";
       if(P1!=NULL)
       {
          if (svrType) {if(svrType == 1) hasMoved(11, 1);}
          else P1->isWalk = 0;
       }
       break;
    case Qt::Key_W:
       qDebug()<<"R_W";
       if(P1!=NULL)
       {
          if (svrType) {if(svrType == 1) hasMoved(12, 1);}
          else P1->isWalk = 0;
       }
       break;
    case Qt::Key_A:
       qDebug()<<"R_A";
       if(P1!=NULL)
       {
          if (svrType) {if(svrType == 1) hasMoved(13, 1);}
          else P1->isWalk = 0;
       }
       break;
    case Qt::Key_S:
       qDebug()<<"R_S";
       if(P1!=NULL)
       {
          if (svrType) {if(svrType == 1) hasMoved(14, 1);}
          else P1->isWalk = 0;
       }
       break;
    case Qt::Key_Right:
       qDebug()<<"R_Right";
       if(P2!=NULL)
       {
          if (svrType) {if(svrType == 2) hasMoved(21, 1);}
          else P2->isWalk = 0;
       }
       break;
    case Qt::Key_Up:
       qDebug()<<"R_Up";
       if(P2!=NULL)
       {
          if (svrType) {if(svrType == 2) hasMoved(22, 1);}
          else P2->isWalk = 0;
       }
       break;
    case Qt::Key_Left:
       qDebug()<<"R_Left";
       if(P2!=NULL)
       {
          if (svrType) {if(svrType == 2) hasMoved(23, 1);}
          else P2->isWalk = 0;
       }
       break;
    case Qt::Key_Down:
       qDebug()<<"R_Down";
       if(P2!=NULL)
       {
          if (svrType) {if(svrType == 2) hasMoved(24, 1);}
          else P2->isWalk = 0;
       }
       break;
    }
}

GameWidget::~GameWidget()
{
    if (svr)
    {
        svr->close();
        delete svr;
    }
    if (cli)
    {
        cli->close();
        delete cli;
    }
    delete ui;
}
