#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QObject>
#include <QTcpSocket>
#include <QNetworkInterface>
#include "setting.h"
#include "people.h"

class TcpClientSocket : public QTcpSocket
{
    Q_OBJECT                //添加宏(Q_OBJECT)是为了实现信号与槽的通信
public:
    TcpClientSocket(QObject *parent=0);
private:
    QByteArray outBlock;
signals:
    void updateClients(dataPack p);
    void disconnected(int);
protected slots:
    void dataReceived();
    void slotDisconnected();
};

class Server : public QTcpServer
{
    Q_OBJECT                    //添加宏(Q_OBJECT)是为了实现信号与槽的通信
public:
    Server(QObject *parent=0, int _port=1024);
    ~Server();
    QList<TcpClientSocket*> tcpClientSocketList;
    int connectionNum() { return tcpClientSocketList.count(); }
    void dolisten(QString addr);
    int port = 0;
signals:
    void updateServer(dataPack p);
public slots:
    void updateClients(dataPack p);
    void slotDisconnected(int);
protected:
    void incomingConnection(int socketDescriptor);
};

#endif // SERVER_H

extern Server* svr;
