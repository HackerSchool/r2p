#include "r2p.h"

R2PServer::R2PServer(QObject *parent) :
	QObject(parent)
{
	server = new QTcpServer(this);

	// Bind our newConnection() slot to any new connection.
	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

	// Start listening.
	if (!server->listen(QHostAddress::Any, PORT)) {
		qDebug() << "Error on TCP listen.";
	}
}

void R2PServer::newConnection()
{
	// Grab the connetion's socket.
	QTcpSocket *socket = server->nextPendingConnection();

	// TODO: parse client request & reply

	socket->close();
}
