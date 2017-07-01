#include "ui_client.h"

#include "client.h"

client::client(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::client)
	, settings(new QSettings("HackerSchool", "R2Pclient"))
	, error(QErrorMessage::qtHandler()) // Register graphical debug messages
	, r2p(this, 40000)
{
	ui->setupUi(this);

	remoteAddress = settings->value("host").toString();
	remotePort = settings->value("port").toInt();
	remoteUser = settings->value("user").toString();
	remotePass = settings->value("pass").toString();

	connect(&r2p, &R2P::gotReply, [this](char replyType, QString const reply)
	{
		switch (replyType) {
			case Reply::STREAM_STARTED:
				startFreerdp();
				break;

			case Reply::GAME_LIST:
				gameList = reply.split(SPLIT);
				// TODO: updateGameList();
				break;

			default:
				break;
		}
	});

	connect(&r2p, &R2P::gotRequest, [this](QTcpSocket *const remote,
		char requestType, QString const request)
	{
		QString buf;

		switch (requestType) {
			case Request::STREAM_STARTED:
				buf.append(Reply::OK);
				startFreerdp();
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

void client::startFreerdp()
{
	QProcess process;
	// TODO: move args out of here
	process.execute("xfreerdp", QStringList() <<
			"/multimedia:sys:alsa" << "/cert-tofu" <<
			"/jpeg" << "/jpeg-quality:90" <<
			"/gfx:AVC420" << "+gfx-thin-client" << "+gfx-progressive" << "/gfx-h264:AVC420" <<
			"/rfx" << "/rfx-mode:video" << "/gdi:hw" <<
			"/compression-level:2" << "-decorations" <<
			"+async-input" << "+async-update" << "+async-transport" << "+async-channels" <<
			"+auto-reconnect" << "/auto-reconnect-max-retries: 10" <<
			"/u:" + remoteUser << "/p:" + remotePass << "/v:" + remoteAddress);
}

void client::sendRequest(char requestType, QString payload)
{
	r2p.sendRequest(remoteAddress, remotePort, requestType, payload);
}

void client::on_refreshGamesButton_clicked()
{
	sendRequest(Request::GET_GAME_LIST);
}

void client::on_streamButton_clicked()
{
	sendRequest(Request::START_STREAM);
}

void client::on_configButton_clicked()
{
	cWindow = new ConnectWindow(this, settings);
	cWindow->setAttribute(Qt::WA_DeleteOnClose);

	connect(cWindow, &ConnectWindow::gotInfo, [this] (QString host, int port,
		QString user, QString pass)
	{
		remoteAddress = host;
		remotePort = port;
		remoteUser = user;
		remotePass = pass;
	});
}

void client::on_gameList_clicked(const QModelIndex& index)
{
}
