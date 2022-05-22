#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1028,722);

    QPixmap icon(":/boom/res\\boom\\boomA_1.png");

    para = nullptr;
    this->setWindowTitle("炸弹人");
    this->setWindowIcon(icon);

    connect(ui->Start, &QPushButton::clicked, [=](){
        para = new gamepara(nullptr, 0);
        para->fa = this;
        para->show();
        this->hide();

        connect(para, &gamepara::callClose, this, [=](){delete para; para = nullptr;});

    });
    connect(ui->svrOpen, &QPushButton::clicked, [=](){
        para = new gamepara(nullptr, 1);
        para->fa = this;
        para->show();

        //svr = new Server(nullptr, 1025);
        //cli = new Client(nullptr, 1025);
        //svr->dolisten("192.168.43.103");
        //cli->doconnect("192.168.43.103");

        //game = new GameWidget(nullptr, 1, 0, 1, -1, -1 );
        //game->show();
        this->hide();

        connect(para, &gamepara::callClose, this, [=](){delete para; para = nullptr;});

    });
    connect(ui->cliOpen, &QPushButton::clicked, [=](){
        para = new gamepara(nullptr, 2);
        para->fa = this;
        para->show();

        //cli = new Client(nullptr, 1025);
        //cli->doconnect("127.0.0.1");

        //game = new GameWidget(nullptr, 2, 0, 1, -1, -1 );
        //game->show();
        this->hide();

        connect(para, &gamepara::callClose, this, [=](){delete para; para = nullptr;});

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

