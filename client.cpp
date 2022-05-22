#include "client.h"
#include <QMessageBox>
#include <QHostInfo>

Client* cli = nullptr;

Client::Client(QWidget *parent, int _port)
    : QDialog(parent)
{
    status = false;  //  连接or未连接
    port = _port;
    serverIP =new QHostAddress;

}

void Client::doconnect(QString addr)
{
    serverIP->setAddress(addr);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT (slotConnected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT(slotDisconnected()),Qt::QueuedConnection);
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT (dataReceived()));
    tcpSocket->connectToHost(*serverIP,port);
    qDebug() << "doconnect: " << serverIP->toString() << " : " << port << "  status:" << tcpSocket->isValid();
}

void Client::retry(QString addr)
{
    serverIP->setAddress(addr);
    tcpSocket->connectToHost(*serverIP,port);
}

void Client::slotConnected()
{
    //成功打开连接之后...（初始化）
    status = true;
    qDebug() << "Client: Success Connect" << endl;
    emit connected();
}

void Client::slotSend(dataPack p)
{

    dataPack data;
    data.type = 1;
    data.player = p.player;
    data.move = p.move;

    if(p.move >= 100)
    {
        data.type = p.move;
    }

    QByteArray buffer;
    buffer.append(reinterpret_cast<char*>(&data), sizeof(data));
    tcpSocket->write(buffer.data(), sizeof(data));
    tcpSocket->flush();
    qDebug() << "write to struct to server......";
}

void Client::slotDisconnected()
{
    //成功断开连接之后...(初始化)
    qDebug() << "Client: Success Disconnect" << endl;
}

void Client::dataReceived()
{
    QByteArray buffer;
    buffer = tcpSocket->readAll();
    if (!buffer.isEmpty()) {
        dataPack* p = reinterpret_cast<dataPack*>(buffer.data());

        if(p->type == 1) updateClientW(*p); //emit moveNetPlayer(*p);
        else if(p->type >= 100 && p->type < 1000) emit playerSel(*p);
        else if(p->type == 2000) {emit gamestart_cli(*p); qDebug() << "REV:gameStart";}
        else if(p->type == 2002) {emit cliReady_cli(); }
        //qDebug() << "read from client......" << p->name << "  " << p->age;
        qDebug() << "dataRev: data->type:" << p->type;
    }
}

void Client::updateClientW(dataPack p)
{
    //依据网络更新界面
    if(p.type == 1)
    {
        if (p.player == 1)
        {
            if(p.playerPos[1][0] != P1->X || p.playerPos[1][1] != P1->Y || p.Deviation[1] != P1->deviation)
                P1->MovePos(p.playerPos[1][0], p.playerPos[1][1], p.Deviation[1]);
            if (p.move >= 1 && p.move <= 4)
            {
                P1->Walk(p.move);
                P1->isWalk = 0;
                if (GsvrType == 1) qDebug() << "server: P1 moving..." << endl;
            }
            else if (p.move == 5)
            {
                BoomV.push_back(new BoomA(P1->BoomLv, P1->X, P1->Y, this->fa));
                P1->raise();
            }
            else if (p.move >= 10 && p.move <= 19) P1->isWalk = 0;
        }
        else if (p.player == 2)
        {
            if(p.playerPos[2][0] != P2->X || p.playerPos[2][1] != P2->Y || p.Deviation[2] != P2->deviation)
                P2->MovePos(p.playerPos[2][0], p.playerPos[2][1], p.Deviation[2]);
            if (p.move >= 1 && p.move <= 4)
            {

                P2->Walk(p.move);
                P2->isWalk = 0;
                if (GsvrType == 1) qDebug() << "server: P2 moving..." << endl;
            }
            else if (p.move == 5)
            {
                BoomV.push_back(new BoomA(P2->BoomLv, P2->X, P2->Y, this->fa));
                P2->raise();
            }
            else if (p.move >= 20 && p.move <= 29) P2->isWalk = 0;
        }
    }

}

Client::~Client()
{
    delete tcpSocket;
    delete serverIP;
    qDebug() << "client detroy";
    cli = nullptr;
}
