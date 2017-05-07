#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

#include "r2p.h"

namespace Ui {
	class client;
}

class client : public QMainWindow
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();
    void sendRequest(char requestType, QString payload);

private:
    Ui::client *ui;

	R2P r2p;
	QString remoteAddress;
	int remotePort;
};

#endif // CLIENT_H
