#include "ui_server.h"

#include "server.h"

server::server(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::server)
	, settings(new QSettings("HackerSchool", "R2Pserver"))
	, error(QErrorMessage::qtHandler()) // Register graphical debug messages
	, r2p(this, 40500)
{
	ui->setupUi(this);

	gameList = settings->value("gameList").value<QList<QStringList>>();
	remoteAddress = settings->value("host").toString();
	remotePort = settings->value("port").toInt();

	connect(&r2p, &R2P::gotReply, [](char replyType, QString const reply)
	{
		switch (replyType) {
			case Reply::OK:
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
			case Request::START_STREAM:
				startRDP();
				buf.append(Reply::STREAM_STARTED);
				break;

			case Request::GET_GAME_LIST:
				buf.append(Reply::GAME_LIST);
				for (int i = 0; i < gameList.size(); i++) {
					buf.append(gameList.at(i).at(0));
					buf.append(SPLIT);
				}
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

void server::startRDP()
{
}

void server::sendRequest(char requestType, QString payload)
{
	r2p.sendRequest(remoteAddress, remotePort, requestType, payload);
}

void server::on_addGameButton_clicked()
{
	QString gamePath = QFileDialog::getOpenFileName(this, tr("Select Game"),
		QStringLiteral(""), tr("Executables (*.exe)"));

	if (!gamePath.isEmpty()) {
		gameList.append(QStringList() << QFileInfo(gamePath).baseName() << gamePath);
		settings->setValue("gameList", QVariant::fromValue(gameList));
	}
}

void server::on_connectButton_clicked()
{
	startRDP();
	sendRequest(Request::STREAM_STARTED);
}

void server::on_configButton_clicked()
{
	cWindow = new ConnectWindow(this, settings);
	cWindow->setAttribute(Qt::WA_DeleteOnClose);

	connect(cWindow, &ConnectWindow::gotInfo, [this] (QString host, int port)
	{
		remoteAddress = host;
		remotePort = port;
	});
}

void server::on_gameList_clicked(const QModelIndex& index)
{
}
