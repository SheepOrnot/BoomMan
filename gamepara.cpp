#include "gamepara.h"
#include "ui_gamepara.h"

gamepara::gamepara(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamepara)
{
    ui->setupUi(this);



}

gamepara::~gamepara()
{
    delete ui;
}
