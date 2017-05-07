#include "ui_client.h"

#include "client.h"

client::client(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::client)
	, settings(new QSettings("HackerSchool", "R2Pc"))
	, error(QErrorMessage::qtHandler())
	, r2p(this, 40000)
{
	ui->setupUi(this);

	connect(&r2p, &R2P::gotReply, [](char replyType, QString const reply)
	{
		qDebug() << "got reply" << replyType << reply;
		switch (replyType) {
			case Reply::STREAM_STARTED:
				// TODO: startFreerdp();
			case Reply::GAME_LIST:
				// TODO: updateGameList(reply);

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
			case Request::STREAM_STARTED:
				buf.append(Reply::OK);
                std::system(qPrintable("xfreerdp -u HS -- " + remote->peerName()));
				// TODO: startFreerdp();
				break;

			default:
				break;
		}

		buf.append('\n');
		remote->write(buf.toUtf8());
		remote->flush();
	});
}

client::~client()
{
	delete ui;
	delete settings;
}


void client::sendRequest(char requestType, QString payload)
{
	r2p.sendRequest(remoteAddress, remotePort, requestType, payload);
}

void client::on_refreshGamesButton_clicked()
{
	sendRequest(Request::GET_GAME_LIST);
}

void client::on_connectButton_clicked()
{
	cWindow = new ConnectWindow(this, settings);

	connect(cWindow, &QObject::destroyed, [this]()
	{
		sendRequest(Request::START_STREAM);
	});

	connect(cWindow, &ConnectWindow::gotInfo, [=] (QString host, int port,
		QString user, QString pass)
	{
		remoteAddress = host;
		remotePort = port;
		remoteUser = user;
		remotePass = pass;
	});
}
