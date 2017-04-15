#include "r2p.h"

R2P::R2P(int port)
	: local(new QTcpServer(this))
	, remote(new QTcpSocket(this))
	, buf(new QDataStream)
{
	// Bind our newConnection() slot to any new connection.
	connect(local, SIGNAL(newConnection()), this, SLOT(incomingConnection()));

	// Start listening.
	if (!local->listen(QHostAddress::Any, port)) {
		qDebug() << "Error on TCP listen.";
	}
}

R2P::~R2P()
{
	delete local;
	delete remote;
	delete buf;
}

void R2P::incomingConnection()
{
	// Grab the connetion's socket.
	remote = local->nextPendingConnection();

	// Run our parseRequest() slot when there's any new data on the socket.
    connect(remote, SIGNAL(readyRead()), this, SLOT(parseRequest()));

	// Init our buffer.
	buf->setDevice(remote); // Bind the buffer to our remote socket.
	buf->setVersion(QDataStream::Qt_5_8);
}

void R2P::parseRequest()
{
	buf->startTransaction();

	QString request;
	*buf >> request;

	if (!buf->commitTransaction())
		return;

	// TODO: parse & reply
	qDebug() << request;
}

void R2P::requestGameList()
{
	QByteArray request;
	QDataStream lbuf(&request, QIODevice::WriteOnly);
	lbuf.setVersion(QDataStream::Qt_5_8);

	lbuf << Request::GET_GAME_LIST;

	remote->write(request);
}
