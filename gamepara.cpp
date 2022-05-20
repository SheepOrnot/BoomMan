﻿#include "gamepara.h"
#include "ui_gamepara.h"

gamepara::gamepara(QWidget* parent, int _svrType) :
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

    QPixmap icon(":/boom/res\\boom\\boomA_1.png");

    this->setWindowTitle("炸弹人");
    this->setWindowIcon(icon);

    svrType = _svrType;
    fa = parent;

    if (svrType == 1)
    {
        //hideP2();
        //svr = new Server(this, "127.0.0.1", 1024);
        cli = new Client(this, "127.0.0.1", 1024);
        ui->start->hide();
        ui->JoinSvr->hide();
    }
    else if (svrType == 2)
    {
        //hideP1();
        cli = new Client(this, "127.0.0.1", 1024);
        ui->start->hide();
        ui->CreateSvr->hide();
        ui->connectNum->hide();
        ui->connectNumT->hide();
    }

    if (svrType)
    {
        ui->groupBox_3->hide();
        ui->gamemode->hide();
        ui->playselect->hide();
        ui->groupBox->hide();
        ui->groupBox_2->hide();
    }
    else
    {
        ui->IP->hide();
        ui->labelIP->hide();
        ui->CreateSvr->hide();
        ui->JoinSvr->hide();
        ui->connectNum->hide();
        ui->connectNumT->hide();
    }

    qDebug() << "checkpoint1";

    connect(ui->back, &QPushButton::clicked, [=]()
        {
            fa->show();
            this->close();
            emit callClose();
        });

    connect(ui->CreateSvr, &QPushButton::clicked, [=]()
        {
            QString addr = ui->IP->text();
            if (addr.size() == 0) { QMessageBox::information(nullptr, "啊哦~", "IP地址是空的"); return; }
            if (!svr) svr = new Server(this, addr, 1024);
            if (!cli) cli = new Client(this, addr, 1024);
            else if (cli) cli->retry(addr);

            connect(cli, SIGNAL(connected()), this, SLOT(connectOk()));
            connect(svr, SIGNAL(newConnection()), this, SLOT(newConnect()));
        });

    connect(ui->JoinSvr, &QPushButton::clicked, [=]()
        {
            QString addr = ui->IP->text();
            if (addr.size() == 0) { QMessageBox::information(nullptr, "啊哦~", "IP地址是空的"); return; }
            if (!cli) cli = new Client(this, addr, 1024);
            else if (cli) cli->retry(addr);

            connect(cli, SIGNAL(connected()), this, SLOT(connectOk()));
        });



    connect(ui->pe1v1, &QPushButton::clicked, [=]() {showAll(); hideP2(); });
    connect(ui->pp1v1, &QPushButton::clicked, [=]() {showAll(); });
    connect(ui->ppee2v2, &QPushButton::clicked, [=]() {showAll(); });

    connect(ui->Alex, &QPushButton::clicked, [=]()
        {
            if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
            if (svrType) cli->slotSend(101, 0);
        });
    connect(ui->Dan, &QPushButton::clicked, [=]()
        {
            if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Dan->setChecked(false); return; }
            if (svrType) cli->slotSend(101, 1);
        });
    connect(ui->Molly, &QPushButton::clicked, [=]()
        {
            if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Molly->setChecked(false); return; }
            if (svrType) cli->slotSend(101, 2);
        });
    connect(ui->Roki, &QPushButton::clicked, [=]()
        {
            if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Roki->setChecked(false); return; }
            if (svrType) cli->slotSend(101, 3);
        });

    connect(ui->Alex_2, &QPushButton::clicked, [=]()
        {
            if (svrType == 2 && !cli->isConnected()) { QMessageBox::information(nullptr, "啊哦~", "你还没连接上服务器"); ui->Alex_2->setChecked(false); return; }
            if (svrType) cli->slotSend(102, 0);
        });
    connect(ui->Dan_2, &QPushButton::clicked, [=]()
        {
            if (svrType == 2 && !cli->isConnected()) { QMessageBox::information(nullptr, "啊哦~", "你还没连接上服务器"); ui->Dan_2->setChecked(false); return; }
            if (svrType) cli->slotSend(102, 1);
        });
    connect(ui->Molly_2, &QPushButton::clicked, [=]()
        {
            if (svrType == 2 && !cli->isConnected()) { QMessageBox::information(nullptr, "啊哦~", "你还没连接上服务器"); ui->Molly_2->setChecked(false); return; }
            if (svrType) cli->slotSend(102, 2);
        });
    connect(ui->Roki_2, &QPushButton::clicked, [=]()
        {
            if (svrType == 2 && !cli->isConnected()) { QMessageBox::information(nullptr, "啊哦~", "你还没连接上服务器"); ui->Roki_2->setChecked(false); return; }
            if (svrType) cli->slotSend(102, 3);
        });

    if (svrType) connect(cli, SIGNAL(playerSel(dataPack)), this, SLOT(cliSel(dataPack)));

    connect(ui->start, &QPushButton::clicked, [=]()
        {

            if (ui->pp1v1->isChecked()) gamemode = 2;
            if (ui->pe1v1->isChecked()) gamemode = 3;
            if (ui->ppee2v2->isChecked()) gamemode = 4;
            if (svrType) gamemode = 1;

            if (gamemode == -1) { QMessageBox::information(nullptr, "啊哦~", "游戏模式还没选"); return; }

            if (gamemode == 1)
            {
                if (svrType == 1) checkP1();
                if (svrType == 2) checkP2();

                if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); return; }
                if (!cli->isConnected()) { QMessageBox::information(nullptr, "啊哦~", "你还没连接上服务器"); return; }

                if (pSel1 == -1) { QMessageBox::information(nullptr, "啊哦~", "P1还没选"); return; }
                else if (pSel2 == -1) { QMessageBox::information(nullptr, "啊哦~", "P2还没选"); return; }

            }
            else if (gamemode == 2)
            {
                checkP1();
                checkP2();
                if (pSel1 == -1) { QMessageBox::information(nullptr, "啊哦~", "P1还没选"); return; }
                else if (pSel2 == -1) { QMessageBox::information(nullptr, "啊哦~", "P2还没选"); return; }
            }
            else if (gamemode == 3)
            {
                checkP1();
                checkAI_1();
                if (pSel1 == -1) { QMessageBox::information(nullptr, "啊哦~", "P1还没选"); return; }
            }
            else if (gamemode == 4)
            {
                checkP1();
                checkP2();
                if (pSel1 == -1) { QMessageBox::information(nullptr, "啊哦~", "P1还没选"); return; }
                else if (pSel2 == -1) { QMessageBox::information(nullptr, "啊哦~", "P2还没选"); return; }
                checkAI_2();
            }

            game = new GameWidget(nullptr, svrType, pSel1, pSel2, pSel3, pSel4, gamemode);
            game->show();
            this->close();

        });

}

void gamepara::newConnect()
{
    connectNum++;
    ui->connectNum->setText(QString(connectNum + '0'));
    QMessageBox::information(nullptr, "好诶~", "有新的连接");
}

void gamepara::connectOk()
{
    ui->JoinSvr->hide();
    ui->CreateSvr->hide();
    ui->start->show();
    ui->playselect->show();
    if (svrType == 1) ui->groupBox->show();
    else if (svrType == 2) ui->groupBox_2->show();
    QMessageBox::information(nullptr, "好诶~", "连接成功");
}

void gamepara::cliSel(dataPack p)
{
    if (p.type == 101)
    {
        pSel1 = p.player;
    }
    else if (p.type == 102)
    {
        pSel2 = p.player;
    }
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
    if (ui->Alex->isChecked())   pSel1 = 0;
    if (ui->Dan->isChecked())    pSel1 = 1;
    if (ui->Molly->isChecked())  pSel1 = 2;
    if (ui->Roki->isChecked())   pSel1 = 3;
}

void gamepara::checkP2()
{
    if (ui->Alex_2->isChecked())   pSel2 = 0;
    if (ui->Dan_2->isChecked())    pSel2 = 1;
    if (ui->Molly_2->isChecked())  pSel2 = 2;
    if (ui->Roki_2->isChecked())   pSel2 = 3;
}

void gamepara::checkAI_1()
{
    int vis[4] = { 0 };
    vis[pSel1] = 1;
    for (int i = 0; i < 4; i++)
    {
        if (!vis[i])
        {
            pSel3 = i;
            break;
        }
    }
    return;
}

void gamepara::checkAI_2()
{
    int vis[4] = { 0 };
    vis[pSel1] = 1;
    vis[pSel2] = 1;
    for (int i = 0; i < 4; i++)
    {
        if (!vis[i])
        {
            pSel3 = i;
            vis[i] = 1;
            break;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (!vis[i])
        {
            pSel4 = i;
            break;
        }
    }
    return;
}

gamepara::~gamepara()
{
    qDebug() << "gamepara detroy";
    if (svr) delete svr;
    if (cli) delete cli;
    delete ui;
}
