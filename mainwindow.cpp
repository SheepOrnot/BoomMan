#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
//    ui->setupUi(this);
    game = new GameWidget;
    game->show();
    //connect(ui->Start, SIGNAL(clieck()), this, SLOT(showMain()));
//    connect(ui->Start, &QPushButton::clicked, [=](){
//        game = new GameWidget;
//        game->show();
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

