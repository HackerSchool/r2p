#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QErrorMessage>
#include <QMessageBox>
#include <QFileDialog>

#include "r2p.h"
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
    void startGame(int gameIndex);
    void startRDP();

private slots:
	void on_addGameButton_clicked();
	void on_streamButton_clicked();
	void on_configButton_clicked();

private:
	Ui::server *ui;

	QSettings *settings;
	//QErrorMessage *error;
	R2P r2p;

	// Each game in the list is itself a list in the format:
	// [0]: <name>, [1]: <path>
	QList<QStringList> gameList;
	QString remoteAddress;
	int remotePort;

	ConnectWindow *cWindow;
};

#endif // SERVER_H
