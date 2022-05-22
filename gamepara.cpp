#include "gamepara.h"
#include "ui_gamepara.h"

gamepara::gamepara(QWidget* parent, int _svrType) :
    QMainWindow(parent),
    ui(new Ui::gamepara)
{
    ui->setupUi(this);

    this->setFixedSize(1048,748);

    QPixmap icon(":/boom/res\\boom\\boomA_1.png");

    m_background = new QLabel(this);
    m_background->setGeometry(0,0,1048,748);
    backgroundMovie = new QMovie(":/window/res\\window\\loading.gif",QByteArray(),this);
    backgroundMovie->start();
    m_background->setMovie(backgroundMovie);

    m_background->hide();

    overtime = new QTimer(this);
    connect(overtime, &QTimer::timeout, [=]()
    {
        QMessageBox::information(nullptr, "啊哦~", "连接超时！");
        overtime->stop();
        m_background->hide();
    });

    this->setWindowTitle("炸弹人");
    this->setWindowIcon(icon);


    IPfile = new QFile("./IP.txt");
    bool ret = IPfile->open(QIODevice::ReadOnly | QIODevice::Text);
    if(ret) qDebug() << "File Open Success";
    else qDebug() << "File Open Fail";

    IPfile->readLine(IP, 50);
    ui->IP->setText(IP);
    IPfile->close();

    svrType = _svrType;
    fa = parent;
    mapseed = time(0);

    if (svrType == 1)
    {
        hideP2();
        svr = new Server(this, 1024);
        cli = new Client(this, 1024);
        ui->start->hide();
        ui->JoinSvr->hide();
    }
    else if (svrType == 2)
    {
        hideP1();
        cli = new Client(this, 1024);
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

    if(svrType) connect(cli, SIGNAL(playerSel(dataPack)), this, SLOT(cliSel(dataPack)));
    if(svrType == 2) connect(cli, SIGNAL(connected()), this, SLOT(connectOk()));
    if(svrType == 2) connect(cli, SIGNAL(gamestart_cli(dataPack)), this, SLOT(gamestart_gp(dataPack)));


}

void gamepara::on_back_clicked()
{
    fa->show();
    this->close();
    emit callClose();
}
void gamepara::on_CreateSvr_clicked()
{
    QString addr = ui->IP->text();
    if (addr.size() == 0) { QMessageBox::information(nullptr, "啊哦~", "IP地址是空的"); return; }
    if (!checkIP(addr)) { QMessageBox::information(nullptr, "啊哦~", "IP地址写错了"); return; }

    IPfile->open(QIODevice::WriteOnly | QIODevice::Text |  QIODevice::Truncate);
    QTextStream in(IPfile);
    in << addr;
    IPfile->close();

    svr->dolisten(addr);
    cli->doconnect(addr);

    connect(cli, SIGNAL(connected()), this, SLOT(connectOk()));
    connect(svr, SIGNAL(newConnection()), this, SLOT(newConnect()));
}
void gamepara::on_JoinSvr_clicked()
{
    QString addr = ui->IP->text();
    if (addr.size() == 0) { QMessageBox::information(nullptr, "啊哦~", "IP地址是空的"); return; }
    if (!checkIP(addr)) { QMessageBox::information(nullptr, "啊哦~", "IP地址写错了"); return; }

    IPfile->open(QIODevice::WriteOnly | QIODevice::Text |  QIODevice::Truncate);
    QTextStream in(IPfile);
    in << addr;
    IPfile->close();

    cli->doconnect(addr);

    waitSvrConnect();
}
void gamepara::on_start_clicked()
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

            if(svrType == 1)
            {
                dataPack p;
                p.move = 2000, p.player = mapseed;
                cli->slotSend(p);
            }
            else if(svrType == 2)
            {
                waitSvrStart();
            }

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

        if(svrType != 2)
        {
            gamestart();
        }

    }


void gamepara::on_pe1v1_clicked() {showAll(); hideP2();}
void gamepara::on_pp1v1_clicked() {showAll(); }
void gamepara::on_ppee2v2_clicked() {showAll(); }

void gamepara::on_Alex_clicked()
{
    if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
    if (svrType)
    {
        dataPack p;
        p.move = 101, p.player = 0;
        cli->slotSend(p);
    }
}
void gamepara::on_Alex_2_clicked()
{
    if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
    if (svrType)
    {
        dataPack p;
        p.move = 102, p.player = 0;
        cli->slotSend(p);
    }
}
void gamepara::on_Dan_clicked()
{
    if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
    if (svrType)
    {
        dataPack p;
        p.move = 101, p.player = 1;
        cli->slotSend(p);
    }
}
void gamepara::on_Dan_2_clicked()
{
    if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
    if (svrType)
    {
        dataPack p;
        p.move = 102, p.player = 1;
        cli->slotSend(p);
    }
}
void gamepara::on_Molly_clicked()
{
    if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
    if (svrType)
    {
        dataPack p;
        p.move = 101, p.player = 2;
        cli->slotSend(p);
    }
}
void gamepara::on_Molly_2_clicked()
{
    if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
    if (svrType)
    {
        dataPack p;
        p.move = 102, p.player = 2;
        cli->slotSend(p);
    }
}
void gamepara::on_Roki_clicked()
{
    if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
    if (svrType)
    {
        dataPack p;
        p.move = 101, p.player = 3;
        cli->slotSend(p);
    }
}
void gamepara::on_Roki_2_clicked()
{
    if (svrType == 1 && svr->connectionNum() != 2) { QMessageBox::information(nullptr, "啊哦~", "目前没有其他人连接上服务器"); ui->Alex->setChecked(false); return; }
    if (svrType)
    {
        dataPack p;
        p.move = 102, p.player = 3;
        cli->slotSend(p);
    }
}


bool gamepara::checkIP(QString ip)
{
    if(ip[0] == ' ' || ip[ip.size() - 1] == ' ') return false;

    int dot = 0, numcnt = 0;
    for(int i = 0; i < ip.size(); i ++)
    {
        if(ip[i].isNumber()) numcnt ++;
        else if(ip[i] == '.') dot ++, numcnt = 0;
        else return false;

        if(numcnt >= 4) return false;
    }

    if(dot != 3) return false;
    if(dot == 3 && numcnt == 0) return false;

    return true;
}

void gamepara::waitSvrConnect()
{
    m_background->show();
    overtime->start(5000);
}

void gamepara::waitSvrStart()
{
    m_background->show();
    overtime->start(15000);
}

void gamepara::gamestart()
{
    qDebug() << "gamestart mapseed" << mapseed;
    game = new GameWidget(nullptr, svrType, pSel1, pSel2, pSel3, pSel4, gamemode, mapseed);
    game->show();
    this->hide();
}

void gamepara::gamestart_gp(dataPack p)
{
    qDebug() << "gamestart_gp  mapseed:" << p.player;
    overtime->stop();
    game = new GameWidget(nullptr, svrType, pSel1, pSel2, pSel3, pSel4, gamemode, p.player);
    game->show();
    this->hide();
}

void gamepara::newConnect()
{
    connectNum = svr->connectionNum();
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
    overtime->stop();
    m_background->hide();
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
    delete m_background;
    delete backgroundMovie;
    delete overtime;
    delete IPfile;

    delete ui;
}
