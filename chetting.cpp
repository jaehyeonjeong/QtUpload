#include "chetting.h"
#include "ui_chetting.h"
#include <QtNetwork>
#include <QMessageBox>

#define BLOCK_SIZE 1024

Chetting::Chetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chetting)
{
    ui->setupUi(this);

    /*tcp_server*/
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()), SLOT(clientConnect()));
    if(!tcpServer->listen())
    {
        QMessageBox::critical(this, tr("Echo Server"),
                              tr("Unable to start the server: %1.")\
                              .arg(tcpServer->errorString()));
        close();
        return;
    }

    ui->serverstatus->setText(tr("The server is running on port %1.")
                              .arg(tcpServer->serverPort()));

    ui->textmessage->setReadOnly(true);

    /*tcp client*/
    ui->ipAddress->setText("127.0.0.1");
    QRegularExpression re("^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)."
                          "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$|");

    QRegularExpressionValidator validator(re);
    ui->ipAddress->setPlaceholderText("Server IP Address");

    ui->portNumber->setInputMask("00000;_");
    ui->portNumber->setPlaceholderText("Server Port No");

    /*소켓도 항시 초기화가 필요함*/
    clientSocket = new QTcpSocket(this);
    connect(ui->connectButton,
            &QPushButton::clicked,
            [=]{clientSocket->connectToHost(
                    ui->ipAddress->text(),
                    ui->portNumber->text().toInt());
    });

    connect(ui->sendButton, SIGNAL(clicked()), SLOT(clientsendData()));

    connect(ui->cacelButton,
            &QPushButton::clicked,
            [=]{ui->inputEdit->setText("");});

    connect(clientSocket,
            &QAbstractSocket::errorOccurred,
            [=]{qDebug() << clientSocket->errorString();});
    connect(clientSocket, SIGNAL(readyRead()), SLOT(clientechoData()));
}

/*tcp server*/
void Chetting::echoData()
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE);
    foreach(QTcpSocket *sock, serverList) {
        if(sock != clientConnection)
            sock->write(bytearray);
    }
    ui->serverstatus->setText(QString(bytearray));

}

void Chetting::clientConnect()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection( );
    connect(clientConnection, SIGNAL(disconnected( )), \
            clientConnection, SLOT(deleteLater( )));
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(echoData( )));
    //connect(clientConnection, SIGNAL(disconnected()), SLOT(removeItem()));
    ui->serverstatus->setText("new connection is established...");

    serverList.append(clientConnection);        // QList<QTcpSocket*> clientList;
}

/*tcp client*/
void Chetting::clientsendData() {
    QString str = ui->inputEdit->text();
    if(str.length()) {
        QByteArray bytearray;
        bytearray = str.toUtf8();
        clientSocket->write(bytearray);
    }
}

void Chetting::clientechoData() {
    QTcpSocket *clientSocket = dynamic_cast<QTcpSocket*>(sender());

    if(clientSocket->bytesAvailable() > BLOCK_SIZE) return;

    QByteArray bytearray = clientSocket->read(BLOCK_SIZE);
    ui->textmessage->append(QString(bytearray));
}

Chetting::~Chetting()
{
    delete ui;
}
