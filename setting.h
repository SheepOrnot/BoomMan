#ifndef SETTING_H
#define SETTING_H
#include<QDebug>
#include<QLabel>
#include<QVector>
#include<QMessageBox>
#include<iostream>
#include<QMediaPlayer>
#include<QSoundEffect>

extern int Map[2][16][16];
extern QLabel *Build[16][16];

extern int GsvrType;

typedef struct _dataPack
{
    int type, player, move;
    int playerPos[3][2];
    int Deviation[3];
}dataPack;

#endif // SETTING_H
