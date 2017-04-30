#include "r2p.h"

R2P::R2P(QObject *parent, int localPort)
	: QObject(parent)
	, local(this)
{
    connect(&local, &QTcpServer::acceptError, this, &R2P::socketError);
    connect(&local, &QTcpServer::newConnection, this, &R2P::receiveRequest);

	if (!local.listen(QHostAddress::Any, localPort)) {
		qDebug("Error listening on 0.0.0.0:%d", localPort);
	}
}

R2P::~R2P()
{
}

void R2P::socketError(QAbstractSocket::SocketError error)
{
	qDebug() << "R2P::socketError:" << error;
}

// Receive request
// Messages start with one byte of type Message and end with a newline char.
void R2P::receiveRequest()
{
	QTcpSocket *remote = local.nextPendingConnection();
    connect(remote, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &R2P::socketError);

	QString *request = new QString;
	connect(remote, &QAbstractSocket::readyRead, [=] ()
	{
		request->append(remote->readAll());

		if (request->contains('\n')) {
			qDebug() << "received request" << *request;
			parseRequest(remote, request);
			delete remote;
			delete request;
		}
	});
}

// Send reply
void R2P::parseRequest(QTcpSocket *const remote, QString *const request)
{
	uint8_t requestType = request->toUtf8()[0];
	QString replyBuffer;

	// TODO: Parse request
	switch (requestType)
	{
		case Request::GET_GAME_LIST:
			replyBuffer = Request::GET_GAME_LIST;
			replyBuffer += "Half Life 3" SPLIT "Portal 3" "\n";
			break;

		default:
			// XXX
			break;
	}

	remote->write(replyBuffer.toUtf8());
	qDebug() << "sent reply" << replyBuffer.toUtf8();
	remote->flush();
}

// Send request
void R2P::sendRequest(QString *const remoteAddress, const int remotePort,
	const uint8_t requestType, QString *const payload)
{
	QTcpSocket *remote = new QTcpSocket;
    connect(remote, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &R2P::socketError);

	remote->connectToHost(*remoteAddress, remotePort);
    connect(remote, &QAbstractSocket::connected, [=] ()
    {
		// request = "%d%s\n".format(requestType, payload)
		remote->write(QByteArray(1, requestType).append(*payload).append('\n'));
		qDebug() << "sent request" << QByteArray(1, requestType).append(*payload).append('\n');
		remote->flush();
    });

    // TODO: receive reply & parse & act on it
	QString *reply = new QString;
	connect(remote, &QAbstractSocket::readyRead, [=] ()
	{
		reply->append(remote->readAll());

		if (reply->contains('\n')) {
			delete remote;
			qDebug() << "received reply" << *reply;
			parseReply(*reply);
			delete reply;
		}
	});
}

void R2P::parseReply(QString reply)
{
	uint8_t replyType = reply.toUtf8()[0];

	// TODO: Parse reply
	switch (replyType)
	{
		case Reply::GAME_LIST:
			// showGameList(reply[1:]);
			break;

		default:
			// XXX
			break;
	}
}
