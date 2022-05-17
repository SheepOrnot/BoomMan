#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap btn_start;

    //QPixmap bg = QPixmap(":/floor/res\\window\\MainWindow.png");
    bool ret = btn_start.load(":/button/res\\button\\Start.png");
    QPixmap btn_OnNet = QPixmap(":/button/res\\button\\CreateNetwork.png");
    QPixmap btn_InNet = QPixmap(":/button/res\\button\\JoinNetwork.png");
    //this->setStyleSheet()

    if(!ret){
            qDebug()<<"图片加载失败";
            return;
        }

    //this->setStyleSheet("#MainWindow{border-image: url(:/window/res\\window\\MainWindow.png)}");
    //ui->Start->setIcon(btn_start);
    //ui->Start->setFixedSize(btn_start.width(),btn_start.height());/* 设置图片固定大小 */
    //ui->Start->setStyleSheet(QString("QPushButton{border-image: url(%1);}").arg(":/floor/res\\button\\Start.png"));/* 设置不规则图片样式 */
    //ui->svrOpen->setFixedSize(btn_OnNet.width(),btn_OnNet.height());/* 设置图片固定大小 */
    //ui->svrOpen->setStyleSheet(QString("QPushButton{border-image: url(%1);}").arg(":/floor/res\\button\\CreateNetwork.png"));/* 设置不规则图片样式 */
    //ui->cliOpen->setFixedSize(btn_InNet.width(),btn_InNet.height());/* 设置图片固定大小 */
    //ui->cliOpen->setStyleSheet(QString("QPushButton{border-image: url(%1);}").arg(":/floor/res\\button\\JoinNetwork.png"));/* 设置不规则图片样式 */

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

