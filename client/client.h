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
	void updateGameList();
    void startFreerdp();

private slots:
    void on_connectButton_clicked();
	void on_streamButton_clicked();
	void on_configButton_clicked();
	void on_gameList_clicked(const QModelIndex& index);

private:
	Ui::client *ui;

	QSettings *settings;
	QErrorMessage *error;
	R2P r2p;

	QStringList gameList;
	QString remoteAddress;
	int remotePort = 0;
	QString remoteUser;
	QString remotePass;

	ConnectWindow *cWindow;
};

#endif // CLIENT_H
