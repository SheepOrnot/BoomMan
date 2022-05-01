#include "tool.h"

int Tool::BaseX = 100 -48;
int Tool::BaseY = 50 -48;
QVector<Tool*> ToolV;
Tool::Tool(int TYPE,int XX,int YY,QWidget *parent = NULL)
{
    X = XX, Y = YY, type = TYPE;
    this->setGeometry(0,0,48,48);
    this->setParent(parent);
    QString str;
    if(type==1) str = QString(":/tool/res\\tool\\heart.png");
    if(type==2) str = QString(":/tool/res\\tool\\lighting.png");
    pix = QPixmap(str);
    if(!pix)
    {
        QMessageBox WR;
        WR.setText("Picture Tool Lose");
        WR.exec();
    }
    this->setPixmap(pix);
    this->move(BaseX+X*48,BaseY+Y*48);
    this->show();
    //P3
    //P4
}