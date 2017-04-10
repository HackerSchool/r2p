#ifndef _R2P_H
#define _R2P_H

#include <QtNetwork>

const int PORT = 53390;

class R2PServer : public QObject
{
	Q_OBJECT

public:
	explicit R2PServer(QObject *parent = 0);

signals:

public slots:
	void newConnection();

private:
	QTcpServer *server;
};

#endif // _R2P_H
