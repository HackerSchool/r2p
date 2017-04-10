#include "r2p.h"

R2PClient::R2PClient(QObject *parent)
	: QObject(parent)
	, server(new QTcpServer(this))
{
	// Bind our newConnection() slot to any new connection.
	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

	// Start listening.
	if (!server->listen(QHostAddress::Any, PORT)) {
		qDebug() << "Error on TCP listen.";
	}
}

void R2PClient::newConnection()
{
	// Grab the connetion's socket.
	socket = server->nextPendingConnection();

	// Run our parseRequest() slot when there's any new data on the socket.
    connect(socket, SIGNAL(readyRead()), this, SLOT(parseRequest()));

	// Init our buffer.
	buf.setDevice(socket); // Bind the buffer to our remote socket.
	buf.setVersion(QDataStream::Qt_5_8);
}

void R2PClient::parseRequest()
{
	buf.startTransaction();

	QString request;
	buf >> request;

	if (!buf.commitTransaction())
		return;

	// TODO: parse & reply
	qDebug() << request;
}
