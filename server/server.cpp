#include "ui_server.h"

#include "server.h"

server::server(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::server)
	, settings(new QSettings("HackerSchool", "R2Ps"))
	, error(QErrorMessage::qtHandler())
	, r2p(this, 40500)
{
	ui->setupUi(this);

	connect(&r2p, &R2P::gotReply, [](char replyType, QString const reply)
	{
		qDebug() << "got reply" << replyType << reply;
		switch (replyType) {
			case Reply::OK:
				break;

			default:
				break;
		}
	});

	connect(&r2p, &R2P::gotRequest, [](QTcpSocket *const remote,
		char requestType, QString const request)
	{
		qDebug() << "got request" << requestType << request;
		QString buf;
		switch (requestType) {
			case Request::START_STREAM:
				// TODO: startRDP();
				buf.append(Reply::STREAM_STARTED);
				break;

			case Request::GET_GAME_LIST:
				buf.append(Reply::GAME_LIST);
				// TODO: buf.append(gameListSeparatedBySPLIT);
				break;

			default:
				break;
		}

		buf.append('\n');
		remote->write(buf.toUtf8());
		remote->flush();
	});
}

server::~server()
{
	delete ui;
	delete settings;
}

void server::sendRequest(char requestType, QString payload)
{
	r2p.sendRequest(remoteAddress, remotePort, requestType, payload);
}

void server::on_addGameButton_clicked()
{
	browser = new FileBrowser(this);
	browser->show();
	// TODO: updateGameList(newPath)
}

void server::on_connectButton_clicked()
{
	cWindow = new ConnectWindow(this, &remoteAddress, &remotePort, settings);

	connect(cWindow, &QObject::destroyed, [this]() {
		// TODO: startRDP();
		sendRequest(Request::STREAM_STARTED);
	});
}
