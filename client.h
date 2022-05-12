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
    Client(QWidget *parent = 0,Qt::WindowFlags f=0);
    ~Client();
private:
    QListWidget *contentListWidget;
    QLineEdit *sendLineEdit;
    QPushButton *sendBtn;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QLabel *serverIPLabel;
    QLineEdit *serverIPLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QPushButton *enterBtn;
    QGridLayout *mainLayout;
    bool status;
    int port;
    QHostAddress *serverIP;
    QString userName;
    QTcpSocket *tcpSocket;
signals:
    void moveNetPlayer(dataPack p);
public slots:
    void slotEnter();
    void slotConnected();
    void slotDisconnected();
    void dataReceived();
    void slotSend(int move, int player);
};

#endif // TCPCLIENT_H
