#ifndef TOOL_H
#define TOOL_H

#include"setting.h"
class Tool :public QLabel
{
public:
    Tool(int TYPE,int XX,int YY,QWidget *parent);
    int X,Y;
    int type;
    QPixmap pix;

    static int BaseX;
    static int BaseY;
};

extern QVector<Tool*> ToolV;
#endif // TOOL_H
