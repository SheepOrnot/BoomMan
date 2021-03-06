#include "server.h"

Server* svr = nullptr;

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()),Qt::QueuedConnection);
}
void TcpClientSocket::dataReceived()
{
    QByteArray buffer;
    buffer = this->readAll();
    if (!buffer.isEmpty()) {
        dataPack* p = reinterpret_cast<dataPack*>(buffer.data());

        emit updateClients(*p);

        qDebug() << "read from client......" << p->player << endl;
    }
}
void TcpClientSocket::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}


Server::Server(QObject *parent, int _port):QTcpServer(parent)
{
    /*
    QString myAddr;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();       //返回所有IP地址，然后进行遍历
    for(int i=0;i<ipAddressesList.length();i++)
    {
        QString myAddr;
        QHostAddress  addr = ipAddressesList.at(i);
        qDebug() << addr.toString();      //打印返回信息
        if(addr.toString().contains("192."))      //筛选
        {
            myAddr = addr.toString();
            qDebug() <<myAddr;
            qDebug() << "***************";
            //ui->Edit_serve_IP->setText(myAddr);
        }
    }
    */

    port = _port;


}

void Server::dolisten(QString addr)
{
    int ret = listen(QHostAddress(addr),port);
    if(!ret)
    {
        qDebug() << "listen failed";
    }
    else
    {
        qDebug() << "listen successed";
    }
    this->setMaxPendingConnections(4);     //设置监听数量
    qDebug() << "dolisten: " << addr << " : " << port;
}

void Server::incomingConnection(int socketDescriptor)
{
    TcpClientSocket *tcpClientSocket=new TcpClientSocket(this);
                                                            //(a)
    connect(tcpClientSocket,SIGNAL(updateClients(dataPack)),
            this,SLOT(updateClients(dataPack)));			//(b)
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,
            SLOT(slotDisconnected(int)));					//(c)
    tcpClientSocket->setSocketDescriptor(socketDescriptor);
                                                            //(d)
    tcpClientSocketList.append(tcpClientSocket);			//(e)
}
void Server::updateClients(dataPack p)
{
    dataPack data;
    data.type = p.type;
    if(data.type >= 100)
    {
        data.player = p.player;
    }
    else if(data.type == 1)
    {
        data.playerPos[1][0] = P1->X;
        data.playerPos[1][1] = P1->Y;
        data.playerPos[2][0] = P2->X;
        data.playerPos[2][1] = P2->Y;
        data.Deviation[1] = P1->deviation;
        data.Deviation[2] = P2->deviation;

        data.player = p.player;
        data.move = p.move;
    }


    for(int i=0;i<tcpClientSocketList.count();i++)          //(b)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);

        QByteArray buffer;
        buffer.append(reinterpret_cast<char*>(&data), sizeof(data));
        item->write(buffer.data(), sizeof(data));
        item->flush();
        qDebug() << "write to struct to Clients......" << i;
    }
}
void Server::slotDisconnected(int descriptor)
{
    for(int i=0;i<tcpClientSocketList.count();i++)
    {
        QTcpSocket *item = tcpClientSocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            tcpClientSocketList.removeAt(i);
            return;
        }
    }
    return;
}

Server::~Server()
{
    for(int i = 0; i < tcpClientSocketList.size(); i ++ )
    {
        delete tcpClientSocketList[i];
    }
    qDebug() << "server detroy";
    svr = nullptr;
    return;
}
