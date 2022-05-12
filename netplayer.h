#ifndef NETPLAYER_H
#define NETPLAYER_H

#include "people.h"
#include "server.h"
#include "client.h"

class netPlayer : public people
{
public:
    netPlayer(int TYPE,int XX,int YY,QString NAME = "Unnamed",QWidget *parent = NULL);
    int getMove();

private:



};

extern netPlayer *NP1;

#endif // NETPLAYER_H
