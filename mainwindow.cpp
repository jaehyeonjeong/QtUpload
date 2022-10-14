#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientmanager.h"
#include "productmanager.h"
#include "shoppingmanager.h"
#include "tcpclient.h"
#include "tcpserver.h"

#include <QMdiSubWindow>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clientmanager = new ClientManager(this);
    productmanager = new ProductManager(this);
    shoppingmanager = new ShoppingManager(this);

//    TCPServer* tcpserver;
//    TCPClient* tcpclient;
    tcpserver = new TCPServer(this);
    tcpclient = new TCPClient(this);

    ui->tabWidget->addTab(clientmanager, tr("&ClientTab"));
    ui->tabWidget->addTab(productmanager, tr("&ProductTab"));
    //ui->tabWidget->addTab(shoppingmanager, tr("&ShoppingTab"));

//    QMdiArea mdiArea;
//    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
//    subWindow1->setWidget(internalWidget1);
//    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
//    mdiArea.addSubWindow(subWindow1);

//    QMdiSubWindow *subWindow2 =
//        mdiArea.addSubWindow(internalWidget2);

    subWindow = new QMdiSubWindow;
    subWindow->setWidget(shoppingmanager);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowTitle("Shopping Window");
    subWindow->resize(600, 600);
    ui->mdiArea->addSubWindow(subWindow);

    /*TCP 채팅 위젯 추가*/
    TcpSubWindow[0] = new QMdiSubWindow;
    TcpSubWindow[0]->setWidget(tcpserver);
    TcpSubWindow[0]->setAttribute(Qt::WA_DeleteOnClose);
    TcpSubWindow[0]->setWindowTitle("TcpServer");
    ui->mdiArea->addSubWindow(TcpSubWindow[0]);

    TcpSubWindow[1] = new QMdiSubWindow;
    TcpSubWindow[1]->setWidget(tcpclient);
    TcpSubWindow[1]->setAttribute(Qt::WA_DeleteOnClose);
    TcpSubWindow[1]->setWindowTitle("TcpClient");
    ui->mdiArea->addSubWindow(TcpSubWindow[1]);


    /*탭과 MDIAREA 스핀로드*/
    QList<int> list;
    list << 700 << 600;
    ui->splitter->setSizes(list);

    /*메인윈도우에서 데이터 커넥트*/
    connect(clientmanager, SIGNAL(ClientAdded(QString)),
            shoppingmanager, SLOT(CreceiveData(QString)));

    connect(productmanager, SIGNAL(ProductAdded(QString)),
            shoppingmanager, SLOT(PreceiveData(QString)));

    connect(productmanager, SIGNAL(ProductPrices(QString)),
            shoppingmanager, SLOT(PreceivePrice(QString)));

    this->resize(1300, 600);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete clientmanager;
    delete productmanager;
    delete shoppingmanager;
}

