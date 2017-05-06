#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include "fileBrowser.h"
#include "connectWindow.h"
#include "../r2p/r2p.h"

namespace Ui {
	class server;
}

class server : public QMainWindow
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = nullptr);
    ~server();
    void sendRequest(char requestType, QString payload);

public slots:
    void openFileBrowser();


private slots:
    void on_ConnectButton_clicked();
    void on_addGameButton_clicked();

private:
    Ui::server *ui;

	R2P r2p;
	QString remoteAddress;
	int remotePort;

    FileBrowser *browser;
    ConnectWindow *cWindow;
};

#endif // SERVER_H
