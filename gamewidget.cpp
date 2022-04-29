#include "gamewidget.h"
#include "ui_gamewidget.h"

int GameWidget::AISpeed = 500;

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
    this->setFixedSize(960,960);/*设置固定大小*/

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
            label->move(100+(j-1)*48,50+(i-1)*48);

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
            Build[i][j]->move(100+(j-1)*48,50+(i-1)*48);

        }
    }

    P1 = new people(0,1,1,"P1",this);
    P2 = new people(0,15,15,"P2",this);
    //AI = new people(0,12,12,"AI",this);

    AIComputing = 0;
    //是否开启AI
    if(1)
    {
        AI = new people(0,12,12,"AI",this);

        AITime = new QTimer;
        AITime->start(AISpeed);

        connect(AITime,&QTimer::timeout,[=](){
            if(AIComputing) return;
            AIComputing = 1;
            try{
                auto move = ComputeMove(BoomV, AI, P1);
                if(move >= 1 && move <= 4)
                    if(AI->Check(move))
                    {
                        AI->Walk(move);
                        AI->isWalk=0;
                    }
            }catch(int e)
            {
                qDebug() << e << endl;
            }
            AIComputing = 0;
        });
    }

}
void GameWidget::keyPressEvent(QKeyEvent *event)
{
//    if(event->isAutoRepeat()) return;
    switch(event->key())
    {
    case Qt::Key_Escape:
       qDebug()<<"Escape";
       break;
    case Qt::Key_D:
       qDebug()<<"D";
       P1->Walk(1);
       break;
    case Qt::Key_W:
       qDebug()<<"W";
       P1->Walk(2);
       break;
    case Qt::Key_A:
       qDebug()<<"A";
       P1->Walk(3);
       break;
    case Qt::Key_S:
       qDebug()<<"S";
       P1->Walk(4);
       break;
    case Qt::Key_Space:
       qDebug()<<"Space";
       if(P1->CanBoom())
       BoomV.push_back(new BoomA(0,P1->X,P1->Y,this));
       P1->raise();
       break;
    case Qt::Key_Right:
       qDebug()<<"Right";
       P2->Walk(1);
       break;
    case Qt::Key_Up:
       qDebug()<<"Up";
       P2->Walk(2);
       break;
    case Qt::Key_Left:
       qDebug()<<"Left";
       P2->Walk(3);
       break;
    case Qt::Key_Down:
       qDebug()<<"Down";
       P2->Walk(4);
       break;
    case Qt::Key_Enter:
       qDebug()<<"Enter";
       if(P2->CanBoom())
       BoomV.push_back(new BoomA(0,P2->X,P2->Y,this));
       P2->raise();
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
    delete ui;
}
