#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //game = new GameWidget;
    //game->show();
    //connect(ui->Start, SIGNAL(clieck()), this, SLOT(showMain()));
    connect(ui->Start, &QPushButton::clicked, [=](){
        game = new GameWidget(nullptr, 0);
        game->show();
    });
    connect(ui->svrOpen, &QPushButton::clicked, [=](){
        game = new GameWidget(nullptr, 1);
        game->show();
    });
    connect(ui->cliOpen, &QPushButton::clicked, [=](){
        game = new GameWidget(nullptr, 2);
        game->show();
    });
    //this->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

