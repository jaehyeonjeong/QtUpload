#ifndef CHETTING_H
#define CHETTING_H

#include <QWidget>
#include <QDataStream>

class QTextEdit;
class QLineEdit;
class QTcpSocket;
class QTcpServer;

//typedef struct{
//    int type;
//    char data[1020];
//}chatProtocolType;

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
    void removeItem();

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
