#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ClientManager;
class ProductManager;
class ShoppingManager;
class TCPServer;
class TCPClient;

class QMdiSubWindow;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //    QMdiArea mdiArea;
    //    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    //    subWindow1->setWidget(internalWidget1);
    //    subWindow1->setAttribute(Qt::WA_DeleteOnClose);
    //    mdiArea.addSubWindow(subWindow1);

    //    QMdiSubWindow *subWindow2 =
    //        mdiArea.addSubWindow(internalWidget2);

private:
    Ui::MainWindow *ui;
    ClientManager* clientmanager;
    ProductManager* productmanager;
    ShoppingManager* shoppingmanager;

    TCPServer* tcpserver;
    TCPClient* tcpclient;

    QMdiSubWindow* subWindow;
    QMdiSubWindow* TcpSubWindow[2];
};
#endif // MAINWINDOW_H
