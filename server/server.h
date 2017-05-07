#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QErrorMessage>

#include "r2p.h"
#include "fileBrowser.h"
#include "connectWindow.h"

namespace Ui {
	class server;
}

class server : public QMainWindow
{
	Q_OBJECT

public:
	explicit server(QWidget *parent = nullptr);
	~server();
	void sendRequest(char requestType, QString payload = "");

private slots:
	void on_connectButton_clicked();
	void on_addGameButton_clicked();

private:
	Ui::server *ui;

	QSettings *settings;
	QErrorMessage *error;
	R2P r2p;
	QString remoteAddress;
	int remotePort;

	FileBrowser *browser;
	ConnectWindow *cWindow;
};

#endif // SERVER_H
