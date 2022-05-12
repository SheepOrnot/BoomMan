#include "netplayer.h"

netPlayer *NP1 = NULL;

netPlayer::netPlayer(int TYPE,int XX,int YY,QString NAME,QWidget *parent) : people(TYPE, XX, YY, NAME, parent)
{

}

/*
int netPlayer::getMove()
{

}
*/
