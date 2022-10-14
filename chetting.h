#ifndef CHETTING_H
#define CHETTING_H

#include <QWidget>

#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Chetting;
}

class Chetting : public QWidget
{
    Q_OBJECT

public:
    explicit Chetting(QWidget *parent = nullptr);

    ~Chetting();

private slots:
    /*server slots*/
    void clientConnect();
    void echoData();

    /*client slots*/
    void clientechoData();
    void clientsendData();
private:
    Ui::Chetting *ui;
    /*tcp server*/
    QTcpServer* tcpServer;
    QList<QTcpSocket*> serverList;

    /*tcp client*/
    QTcpSocket* clientSocket;
    //QList<QTcpSocket*> clientList;
};

#endif // CHETTING_H
