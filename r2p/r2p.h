#ifndef R2P_H
#define R2P_H

#include <QtNetwork>

#include "r2p_global.h"

const int PORT = 53390;

namespace Request {
	enum {GET_GAME_LIST, START_STREAM};
};

namespace Reply {
	enum {GAME_LIST, STREAM_STARTED};
};

class R2PSHARED_EXPORT R2P : public QObject
{
	Q_OBJECT

public:
	explicit R2P(int port = PORT);
	~R2P();
	void requestGameList();

public slots:
	void incomingConnection();
	void parseRequest();

private:
	QTcpServer *local = 0; // Ourselves
	QTcpSocket *remote = 0; // The other r2p app
	QDataStream *buf = 0; // Buffer for the request from `remote`.


};

#endif // R2P_H
