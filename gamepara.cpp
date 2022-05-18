#include "gamepara.h"
#include "ui_gamepara.h"

gamepara::gamepara(QWidget *parent, int svrType) :
    QMainWindow(parent),
    ui(new Ui::gamepara)
{
    ui->setupUi(this);

    //QGraphicsOpacityEffect *groupBox = new QGraphicsOpacityEffect;
    //QGraphicsOpacityEffect *Button = new QGraphicsOpacityEffect;
    //groupBox->setOpacity(0.1);
    //Button->setOpacity(1);
    //ui->groupBox->setGraphicsEffect(groupBox);
    //ui->groupBox_2->setGraphicsEffect(groupBox);
    //ui->groupBox_3->setGraphicsEffect(groupBox);

    //ui->Alex->setGraphicsEffect(Button);
    //ui->Dan->setGraphicsEffect(Button);
    //ui->Molly->setGraphicsEffect(Button);
    //ui->Roki->setGraphicsEffect(Button);

    if(svrType == 1) hideP2();
    if(svrType == 2) hideP1();
    if(svrType)
    {
        ui->groupBox_3->hide();
    }

    connect(ui->pe1v1, &QPushButton::clicked, [=](){showAll();hideP2();});
    connect(ui->pp1v1, &QPushButton::clicked, [=](){showAll();});
    connect(ui->ppee2v2, &QPushButton::clicked, [=](){showAll();});

    connect(ui->start, &QPushButton::clicked, [=]()
    {

        if(ui->pp1v1->isChecked()) gamemode = 2;
        if(ui->pe1v1->isChecked()) gamemode = 3;
        if(ui->ppee2v2->isChecked()) gamemode = 4;
        if(svrType) gamemode = 1;

        if(gamemode == -1) {QMessageBox::information(nullptr, "啊哦~", "游戏模式还没选"); return;}

        if(gamemode == 1)
        {
            if(svrType == 1) checkP1();
            if(svrType == 2) checkP2();
            if(pSel1 == -1) {QMessageBox::information(nullptr, "啊哦~", "P1还没选"); return; }
            else if(pSel2 == -1) {QMessageBox::information(nullptr, "啊哦~", "P2还没选"); return;}
        }
        else if(gamemode == 2)
        {
            checkP1();
            checkP2();
            if(pSel1 == -1) {QMessageBox::information(nullptr, "啊哦~", "P1还没选"); return; }
            else if(pSel2 == -1) {QMessageBox::information(nullptr, "啊哦~", "P2还没选"); return;}
        }
        else if(gamemode == 3)
        {
            checkP1();
            checkAI_1();
            if(pSel1 == -1) {QMessageBox::information(nullptr, "啊哦~", "P1还没选"); return; }
        }
        else if(gamemode == 4)
        {
            checkP1();
            checkP2();
            if(pSel1 == -1) {QMessageBox::information(nullptr, "啊哦~", "P1还没选"); return; }
            else if(pSel2 == -1) {QMessageBox::information(nullptr, "啊哦~", "P2还没选"); return;}
            checkAI_2();
        }

        game = new GameWidget(nullptr, svrType, pSel1, pSel2, pSel3, pSel4, gamemode);
        game->show();
        this->close();

    });

}

void gamepara::showAll()
{
    ui->groupBox->show();
    ui->groupBox_2->show();
}

void gamepara::hideP1()
{
    ui->groupBox->hide();
}

void gamepara::hideP2()
{
    ui->groupBox_2->hide();
}

void gamepara::checkP1()
{
    if(ui->Alex->isChecked())   pSel1 = 0;
    if(ui->Dan->isChecked())    pSel1 = 1;
    if(ui->Molly->isChecked())  pSel1 = 2;
    if(ui->Roki->isChecked())   pSel1 = 3;
}

void gamepara::checkP2()
{
    if(ui->Alex_2->isChecked())   pSel2 = 0;
    if(ui->Dan_2->isChecked())    pSel2 = 1;
    if(ui->Molly_2->isChecked())  pSel2 = 2;
    if(ui->Roki_2->isChecked())   pSel2 = 3;
}

void gamepara::checkAI_1()
{
    int vis[4] = {0};
    vis[pSel1] = 1;
    for(int i = 0; i < 4; i ++)
    {
        if(!vis[i])
        {
            pSel3 = i;
            break;
        }
    }
    return;
}

void gamepara::checkAI_2()
{
    int vis[4] = {0};
    vis[pSel1] = 1;
    vis[pSel2] = 1;
    for(int i = 0; i < 4; i ++)
    {
        if(!vis[i])
        {
            pSel3 = i;
            break;
        }
    }
    for(int i = 0; i < 4; i ++)
    {
        if(!vis[i])
        {
            pSel4 = i;
            break;
        }
    }
    return;
}

gamepara::~gamepara()
{
    delete ui;
}
