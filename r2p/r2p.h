#ifndef R2P_H
#define R2P_H

#include <QtNetwork>

typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);

const int PORT = 53390;

namespace Request {
	enum : char {GET_GAME_LIST = 1, START_STREAM};
}
namespace Reply {
	enum : char {GAME_LIST = 1, STREAM_STARTED};
}
#define SPLIT "\x01"

class R2P : public QObject
{
	Q_OBJECT

public:
	explicit R2P(QObject *parent = nullptr, int localPort = PORT);
	~R2P();

	void sendRequest(const QString remoteAddress, const int remotePort,
		const char requestType, const QString payload);

private:
	QTcpServer local;
	void receiveRequest();
	void parseRequest(QTcpSocket *const remote, QString *const request);
	void parseReply(QString reply);

	void socketError(QAbstractSocket::SocketError error);
};

#endif // R2P_H
