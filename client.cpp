#include "client.h"
#include <QMessageBox>
#include <QHostInfo>

Client* cli = nullptr;

Client::Client(QWidget *parent, QString addr, int _port)
    : QDialog(parent)
{
    status = false;  //  连接or未连接
    port = _port;
    serverIP =new QHostAddress(addr);

    /* 创建了一个QTcpSocket类对象，并将信号/槽连接起来 */
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket,SIGNAL(connected()),this,SLOT (slotConnected()));
    connect(tcpSocket,SIGNAL(disconnected()),this,SLOT (slotDisconnected ()));
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT (dataReceived()));
    tcpSocket->connectToHost(*serverIP,port);


    //tcpSocket->disconnectFromHost();
    //status=false;

}

void Client::slotConnected()
{
    //成功打开连接之后...（初始化）
    status = true;
    qDebug() << "Client: Success Connect" << endl;
}

void Client::slotSend(int move, int player)
{

    dataPack data;
    data.type = 1;
    data.player = player;
    data.move = move;

    if(move >= 100)
    {
        data.type = move;
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

        if(p->type == 1) emit moveNetPlayer(*p);
        else if(p->type >= 100) emit playerSel(*p);
        //qDebug() << "read from client......" << p->name << "  " << p->age;
    }
}

Client::~Client()
{

}
