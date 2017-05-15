#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QErrorMessage>

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
    void startFreerdp();

private slots:
    void on_refreshGamesButton_clicked();
	void on_connectButton_clicked();

private:
	Ui::client *ui;

	QSettings *settings;
	QErrorMessage *error;
	R2P r2p;
	QString remoteAddress;
	int remotePort;
	QString remoteUser;
	QString remotePass;

	ConnectWindow *cWindow;
};

#endif // CLIENT_H
