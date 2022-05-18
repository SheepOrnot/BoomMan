#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    connect(ui->Start, &QPushButton::clicked, [=](){
        game = new GameWidget(nullptr, 0);
        game->show();
        this->close();
    });
    connect(ui->svrOpen, &QPushButton::clicked, [=](){
        game = new GameWidget(nullptr, 1);
        game->show();
        this->close();
    });
    connect(ui->cliOpen, &QPushButton::clicked, [=](){
        game = new GameWidget(nullptr, 2);
        game->show();
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

