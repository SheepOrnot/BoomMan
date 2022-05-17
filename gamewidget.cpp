#include "gamewidget.h"
#include "ui_gamewidget.h"

int GameWidget::AISpeed = 150;

GameWidget::GameWidget(QWidget *parent, int _svrType) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    this->setFixedSize(960,790);/*设置固定大小*/
    this->setWindowFlags(Qt::FramelessWindowHint);

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
            //绘制图片
            QPixmap pix = QPixmap(":/floor/res\\floor\\item1.png");
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

    P1 = new people(1,1,1,"P1",this);
    P2 = new people(2,15,15,"P2",this);
    //AI = new people(0,12,12,"AI",this);

    AIComputing = 0;
    //是否开启AI
    if(0)
    {
        AI = new AIPlayer(0,13,15,"AI",this);
        AIp = AI;

        AITime = new QTimer;
        AITime->start(AISpeed);

        connect(AITime,&QTimer::timeout,[=](){
            if(AIComputing) return;
            AIComputing = 1;
            try{
                int move = ComputeMove(*AI);
                //std::cerr << "receiveMoveCtrl:" << move << std::endl;
                if(move >= 1 && move <= 4)
                    if(AI->Check(move))
                    {
                        AI->Walk(move);
                        AI->isWalk=0;
                    }
                if(move == 5) BoomV.push_back(new BoomA(AI->BoomLv, AI->X, AI->Y, this));
            }catch(int e)
            {
                qDebug() << e << endl;
            }
            AIComputing = 0;
        });
    }

    svr = nullptr;
    cli = nullptr;
    svrType = _svrType;

    //是否开启服务器
    if (svrType == 1)
    {
        qDebug() << "open server" << endl;
        svr = new Server(this, 1024);
        cli = new Client(this);

        //客户端信息直接发送给服务端处理moveNetPlayer
        connect(this, SIGNAL(hasMoved(int, int)), cli, SLOT(slotSend(int, int)));               //发送数据到服务器
        connect(cli, SIGNAL(moveNetPlayer(dataPack)), this, SLOT(updateClient(dataPack)));      //本地移动
    }
    //开启一个客户端
    else if (svrType == 2)
    {
        qDebug() << "open client" << endl;
        cli = new Client(this);

        //客户端信息直接发送给服务端处理
        connect(this, SIGNAL(hasMoved(int, int)), cli, SLOT(slotSend(int, int)));               //发送数据到服务器
        connect(cli, SIGNAL(moveNetPlayer(dataPack)), this, SLOT(updateClient(dataPack)));      //本地移动
    }

}

void GameWidget::updateClient(dataPack p)
{
    //依据网络更新界面
    if (p.player == 1)
    {
        if(p.playerPos[1][0] != P1->X || p.playerPos[1][1] != P1->Y)
            P1->MovePos(p.playerPos[1][0], p.playerPos[1][1], P1->deviation);
        if (p.move >= 1 && p.move <= 4)
        {
            P1->Walk(p.move);
            P1->isWalk = 0;
            if (svrType == 1) qDebug() << "server: P1 moving..." << endl;
        }
        else if (p.move == 5)
        {
            BoomV.push_back(new BoomA(P1->BoomLv, P1->X, P1->Y, this));
            P1->raise();
        }
    }
    else if (p.player == 2)
    {
        if(p.playerPos[2][0] != P2->X || p.playerPos[2][1] != P2->Y)
            P2->MovePos(p.playerPos[2][0], p.playerPos[2][1], P2->deviation);
        if (p.move >= 1 && p.move <= 4)
        {

            P2->Walk(p.move);
            P2->isWalk = 0;
            if (svrType == 1) qDebug() << "server: P2 moving..." << endl;
        }
        else if (p.move == 5)
        {
            BoomV.push_back(new BoomA(P2->BoomLv, P2->X, P2->Y, this));
            P2->raise();
        }
    }

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
        if (svrType) {if(svrType == 1) emit hasMoved(1, 1);}
        else P1->Walk(1);
        break;
    case Qt::Key_W:
        qDebug() << "W";
        if (svrType) {if(svrType == 1) emit hasMoved(2, 1);}
        else P1->Walk(2);
        break;
    case Qt::Key_A:
        qDebug() << "A";
        if (svrType) {if(svrType == 1) emit hasMoved(3, 1);}
        else P1->Walk(3);
        break;
    case Qt::Key_S:
        qDebug() << "S";
        if (svrType) {if(svrType == 1) emit hasMoved(4, 1);}
        else P1->Walk(4);
        break;
    case Qt::Key_Space:
        qDebug() << "Space";
        if (P1->CanBoom())
        {
            if (svrType) {if(svrType == 1) emit hasMoved(5, 1);}
            else
            {
                BoomV.push_back(new BoomA(P1->BoomLv, P1->X, P1->Y, this));
                P1->raise();
            }
        }
        break;
    case Qt::Key_Right:
        qDebug() << "Right";
        if (svrType) { if(svrType == 2) emit hasMoved(1, 2); }
        else P2->Walk(1);
        break;
    case Qt::Key_Up:
        qDebug() << "Up";
        if (svrType) { if(svrType == 2) emit hasMoved(2, 2); }
        else P2->Walk(2);
        break;
    case Qt::Key_Left:
        qDebug() << "Left";
        if (svrType) { if(svrType == 2) emit hasMoved(3, 2); }
        else P2->Walk(3);
        break;
    case Qt::Key_Down:
        qDebug() << "Down";
        if (svrType) { if(svrType == 2) emit hasMoved(4, 2); }
        else P2->Walk(4);
        break;
    case Qt::Key_Enter:
        qDebug() << "Enter";
        if (P2->CanBoom())
            if (svrType) {if(svrType == 2) emit hasMoved(5, 2);}
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
       P1->isWalk = 0;
       break;
    case Qt::Key_W:
       qDebug()<<"R_W";
       P1->isWalk = 0;
       break;
    case Qt::Key_A:
       qDebug()<<"R_A";
       P1->isWalk = 0;
       break;
    case Qt::Key_S:
       qDebug()<<"R_S";
       P1->isWalk = 0;
       break;
    case Qt::Key_Right:
       qDebug()<<"R_Right";
       P2->isWalk = 0;
       break;
    case Qt::Key_Up:
       qDebug()<<"R_Up";
       P2->isWalk = 0;
       break;
    case Qt::Key_Left:
       qDebug()<<"R_Left";
       P2->isWalk = 0;
       break;
    case Qt::Key_Down:
       qDebug()<<"R_Down";
       P2->isWalk = 0;
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
