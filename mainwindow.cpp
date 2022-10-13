#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientmanager.h"
#include "productmanager.h"
#include "shoppingmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clientmanager = new ClientManager(this);
    productmanager = new ProductManager(this);
    shoppingmanager = new ShoppingManager(this);

    ui->tabWidget->addTab(clientmanager, tr("&ClientTab"));
    ui->tabWidget->addTab(productmanager, tr("&ProductTab"));
    ui->tabWidget->addTab(shoppingmanager, tr("&ShoppingTab"));


    /*메인윈도우에서 데이터 커넥트*/
    connect(clientmanager, SIGNAL(ClientAdded(QString)),
            shoppingmanager, SLOT(CreceiveData(QString)));

    connect(productmanager, SIGNAL(ProductAdded(QString)),
            shoppingmanager, SLOT(PreceiveData(QString)));

    connect(productmanager, SIGNAL(ProductPrices(QString)),
            shoppingmanager, SLOT(PreceivePrice(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete clientmanager;
    delete productmanager;
    delete shoppingmanager;
}

