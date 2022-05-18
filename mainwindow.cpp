#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Start, &QPushButton::clicked, [=](){
        para = new gamepara(nullptr, 0);
        para->show();
        this->close();
    });
    connect(ui->svrOpen, &QPushButton::clicked, [=](){
        para = new gamepara(nullptr, 1);
        para->show();
        this->close();
    });
    connect(ui->cliOpen, &QPushButton::clicked, [=](){
        para = new gamepara(nullptr, 2);
        para->show();
        this->close();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

