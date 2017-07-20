#include "ui_client.h"

#include "client.h"

client::client(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::client)
	, settings(new QSettings("HackerSchool", "R2Pclient"))
	//, error(QErrorMessage::qtHandler()) // Register graphical debug messages
	, r2p(this, PORT)
{
	ui->setupUi(this);

	remoteAddress = settings->value("host").toString();
	remotePort = settings->value("port").toInt();
	remoteUser = settings->value("user").toString();
	remotePass = settings->value("pass").toString();

	connect(&r2p, &R2P::error, [this](QString errorMsg)
	{
		QMessageBox::warning(this, tr("Network Error"), errorMsg);
	});

	connect(&r2p, &R2P::gotReply, [this](char replyType, QString const reply)
	{
		switch (replyType) {
			case Reply::STREAM_STARTED:
				startFreerdp();
				break;

			case Reply::GAME_LIST:
				gameList = reply.split(SPLIT);
				updateGameList();
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

void client::updateGameList()
{
	ui->gameList->clear();
	for (int i = 0; i < gameList.size(); i++) {
		new QListWidgetItem(gameList.at(i), ui->gameList);
	}
}

void client::startFreerdp()
{
	// TODO: move args out of here
	QProcess::execute("xfreerdp", QStringList() << "/f" <<
			"/sound:sys:alsa,format:1" << "/cert-tofu" << "/cert-ignore" <<
			"/jpeg" << "/jpeg-quality:10" <<
			"/gfx:AVC420" << "+gfx-thin-client" << "+gfx-progressive" << "/gfx-h264:AVC420" <<
			"/rfx" << "/rfx-mode:video" << "/gdi:hw" <<
			"/compression" << "-decorations" << "-menu-anims" << "/fonts" <<
			"+async-input" << "+async-update" << "+async-transport" << "+async-channels" <<
			"+auto-reconnect" << "/auto-reconnect-max-retries: 10" <<
			"/u:" + remoteUser << "/p:" + remotePass << "/v:" + remoteAddress);
}

void client::sendRequest(char requestType, QString payload)
{
	r2p.sendRequest(remoteAddress, remotePort, requestType, payload);
}

void client::on_connectButton_clicked()
{
	sendRequest(Request::GET_GAME_LIST);
}

void client::on_streamButton_clicked()
{
	sendRequest(Request::START_STREAM, QString::number(ui->gameList->currentRow()));
}

void client::on_configButton_clicked()
{
	cWindow = new ConnectWindow(this, settings);

	connect(cWindow, &ConnectWindow::gotInfo, [this] (QString host, int port,
		QString user, QString pass)
	{
		remoteAddress = host;
		remotePort = port;
		remoteUser = user;
		remotePass = pass;
	});
}
