#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap icon(":/boom/res\\boom\\boomA_1.png");

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
        this->hide();

        connect(para, &gamepara::callClose, this, [=](){delete para; para = nullptr;});

    });
    connect(ui->cliOpen, &QPushButton::clicked, [=](){
        para = new gamepara(nullptr, 2);
        para->fa = this;
        para->show();
        this->hide();

        connect(para, &gamepara::callClose, this, [=](){delete para; para = nullptr;});

    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

