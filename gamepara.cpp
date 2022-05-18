#include "gamepara.h"
#include "ui_gamepara.h"

gamepara::gamepara(QWidget *parent, int svrType) :
    QWidget(parent),
    ui(new Ui::gamepara)
{
    ui->setupUi(this);

    if(svrType == 1) hideP2();
    if(svrType == 2) hideP1();
    if(svrType)
    {
        ui->pe1v1->hide();
        ui->pp1v1->hide();
        ui->ppee2v2->hide();
    }

    connect(ui->start, &QPushButton::clicked, [=]()
    {

        if(ui->pp1v1->isChecked()) gamemode = 2;
        if(ui->pe1v1->isChecked()) gamemode = 3;
        if(ui->ppee2v2->isChecked()) gamemode = 4;
        if(svrType) gamemode = 1;

        if(gamemode == 1)
        {
            if(svrType == 1) checkP1();
            if(svrType == 2) checkP2();
        }
        else if(gamemode == 2)
        {
            checkP1();
            checkP2();
        }
        else if(gamemode == 3)
        {
            checkP1();
            checkAI_1();
        }
        else if(gamemode == 4)
        {
            checkP1();
            checkP2();
            checkAI_2();
        }

        game = new GameWidget(nullptr, svrType, pSel1, pSel2, pSel3, pSel4, gamemode);
        game->show();
        this->close();

    });

}

void gamepara::hideP1()
{
    ui->Alex->hide();
    ui->Dan->hide();
    ui->Molly->hide();
    ui->Roki->hide();
}

void gamepara::hideP2()
{
    ui->Alex_2->hide();
    ui->Dan_2->hide();
    ui->Molly_2->hide();
    ui->Roki_2->hide();
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
