#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QHostAddress>
#include <QTcpSocket>
#include "setting.h"

class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0,QString addr = "",int _port = 1024);
    ~Client();
    bool isConnected() { return status; }
private:
    bool status;
    int port;
    QHostAddress *serverIP;
    QString userName;
    QTcpSocket *tcpSocket;
signals:
    void moveNetPlayer(dataPack p);
    void playerSel(dataPack p);
public slots:
    void slotConnected();
    void slotDisconnected();
    void dataReceived();
    void slotSend(int move, int player);
};

#endif // TCPCLIENT_H


extern Client* cli;
