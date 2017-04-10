#ifndef _R2P_H
#define _R2P_H

#include <QtNetwork>

const int PORT = 53390;

class R2PClient : public QObject
{
	Q_OBJECT

public:
	explicit R2PClient(QObject *parent = 0);

signals:

public slots:
	void newConnection();
	void parseRequest();

private:
	QTcpServer *server; // Ourselves
	QTcpSocket *socket; // The other r2p app
	QDataStream buf; // Buffer for the request from `socket`.
};

#endif // _R2P_H
