#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QWidget>

class Client;
class QMenu;
class QTreeWidgetItem;


namespace Ui {
class ClientManager;
}

class ClientManager : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManager(QWidget *parent = nullptr);
    ~ClientManager();
    QString getClientName();

signals:
    void ClientAdded(QString);

private slots:
    void on_ClientTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void showContextMenu(const QPoint &);
    void removeItem();
    void on_InputButton_clicked();
    void on_CancelButton_clicked();
    void on_ModifyButton_clicked();
    void on_SearchButton_clicked();

    void on_ClientSearchTree_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::ClientManager *ui;
    int makeID();
    QMap<int, Client*> clientList;
    QMenu* menu;
};

#endif // CLIENTMANAGER_H
