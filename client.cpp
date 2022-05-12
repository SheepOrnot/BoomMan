#include "client.h"
#include <QMessageBox>
#include <QHostInfo>
Client::Client(QWidget *parent,Qt::WindowFlags f)
    : QDialog(parent,f)
{
    status = false;  //  连接or未连接
    port = 8010;
    serverIP =new QHostAddress();

    slotEnter();
    //connect(enterBtn,SIGNAL(clicked()),this,SLOT(slotEnter()));         //开启连接
    //connect(sendBtn,SIGNAL(clicked()),this,SLOT(slotSend()));           //发送数据
}

void Client::slotEnter()
{
    if(!status)											//(a)
    {
        QString ip = "127.0.0.1";
        serverIP->setAddress(ip);

        /* 创建了一个QTcpSocket类对象，并将信号/槽连接起来 */
        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,SIGNAL(connected()),this,SLOT (slotConnected()));
        connect(tcpSocket,SIGNAL(disconnected()),this,SLOT (slotDisconnected ()));
        connect(tcpSocket,SIGNAL(readyRead()),this,SLOT (dataReceived()));
        tcpSocket->connectToHost(*serverIP,port);		//(c)
        status=true;
    }
    else
    {
        tcpSocket->disconnectFromHost();				//(f)
        status=false;                                   //将status状态复位
    }
}

void Client::slotConnected()
{
    //成功打开连接之后...（初始化）
    qDebug() << "Client: Success Connect" << endl;
}

void Client::slotSend(int move, int player)
{

    dataPack data;
    data.type = 1;
    data.player = player;
    data.move = move;

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

        emit moveNetPlayer(*p);
        //qDebug() << "read from client......" << p->name << "  " << p->age;
    }
}

Client::~Client()
{

}
