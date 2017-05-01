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
			remote->disconnectFromHost();
			remote->deleteLater();
			delete request;
		}
	});
}

// Send reply
void R2P::parseRequest(QTcpSocket *const remote, QString *const request)
{
	char requestType = request->toUtf8()[0];
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
	remote->flush();
	qDebug() << "sent reply" << replyBuffer.toUtf8();
}

// Send request
void R2P::sendRequest(const QString remoteAddress, const int remotePort,
	const char requestType, const QString payload)
{
	QTcpSocket *remote = new QTcpSocket;
    connect(remote, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error), this, &R2P::socketError);

	remote->connectToHost(remoteAddress, remotePort);

	QByteArray *buf = new QByteArray;
	buf->append(requestType).append(payload).append('\n');

	connect(remote, &QAbstractSocket::connected, [=] ()
    {
		qDebug() << "sent request" << *buf;
		remote->write(*buf);
		remote->flush();
		delete buf;
    });

    // TODO: receive reply & parse & act on it
	QString *reply = new QString;
	connect(remote, &QAbstractSocket::readyRead, [=] ()
	{
		reply->append(remote->readAll());

		if (reply->contains('\n')) {
			remote->disconnectFromHost();
			remote->deleteLater();
			qDebug() << "received reply" << *reply;
			parseReply(*reply);
			delete reply;
		}
	});
}

void R2P::parseReply(QString reply)
{
	char replyType = reply.toUtf8()[0];

	// TODO: Parse reply
	switch (replyType)
	{
		case Reply::GAME_LIST:
			// TODO
			// emit got_game_list
			break;

		default:
			break;
	}
}
