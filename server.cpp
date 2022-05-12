#include "server.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));        //(a)
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected())); //(b)
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


Server::Server(QObject *parent,int port):QTcpServer(parent)
{
    listen(QHostAddress::Any,port);
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
    for(int i = 0; i < 16; i ++ )
    {
        for(int j = 0; j < 16; j ++ )
        {
            data.Map[0][i][j] = p.Map[0][i][j];
        }
    }
    data.player = p.player;
    data.move = p.move;

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
