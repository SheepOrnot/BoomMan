#ifndef SETTING_H
#define SETTING_H
#include<QDebug>
#include<QLabel>
#include<QVector>
#include<QMessageBox>
#include<iostream>

extern int Map[2][16][16];
extern QLabel *Build[16][16];

typedef struct _dataPack
{
    short int type, player, move;
    short int playerPos[3][2];
}dataPack;

#endif // SETTING_H
