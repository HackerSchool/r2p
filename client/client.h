#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

#include "r2p.h"
#include "connectWindow.h"

namespace Ui {
	class client;
}

class client : public QMainWindow
{
	Q_OBJECT

public:
	explicit client(QWidget *parent = nullptr);
	~client();
	void sendRequest(char requestType, QString payload = "");

private slots:
    void on_refreshGamesButton_clicked();
	void on_connectButton_clicked();

private:
	Ui::client *ui;

	QSettings *settings;
	R2P r2p;
	QString remoteAddress;
	int remotePort;

	ConnectWindow *cWindow;
};

#endif // CLIENT_H
