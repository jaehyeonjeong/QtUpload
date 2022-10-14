#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>

#include <QTextEdit>
#include <QLineEdit>
#include <QTcpSocket>


class TCPClient : public QWidget
{
    Q_OBJECT
public:
    explicit TCPClient(QWidget *parent = nullptr);

private slots:
    void echoData();
    void sendData();

private:
    QTextEdit* message;
    QLineEdit* inputLine;
    QTcpSocket* clientSocket;
    QList<QTcpSocket*> clientList;
    QLineEdit* infoLabel;

};

#endif // TCPCLIENT_H
