#include "ui_server.h"

#include "server.h"

server::server(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::server)
	, settings(new QSettings("HackerSchool", "R2Pserver"))
	//, error(QErrorMessage::qtHandler()) // Register graphical debug messages
	, r2p(this, PORT)
{
	ui->setupUi(this);

	gameList = settings->value("gameList").value<QList<QStringList>>();
	for (int i = 0; i < gameList.size(); i++) {
		new QListWidgetItem(gameList.at(i).at(0), ui->gameList);
	}

	remoteAddress = settings->value("host").toString();
	remotePort = settings->value("port").toInt();

	connect(&r2p, &R2P::error, [this](QString errorMsg)
	{
		QMessageBox::warning(this, tr("Network Error"), errorMsg);
	});

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
				startGame(request.toInt());
				startRDP();
				buf.append(Reply::STREAM_STARTED);
				break;

			case Request::GET_GAME_LIST:
				buf.append(Reply::GAME_LIST);
				int i;
				for (i = 0; i < gameList.size() - 1; i++) {
					buf.append(gameList.at(i).at(0));
					buf.append(SPLIT);
				}
				buf.append(gameList.at(i).at(0));
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

void server::startGame(int gameIndex)
{
	if (gameIndex == -1) return;

	QProcess::startDetached(gameList.at(gameIndex).at(0));
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
		new QListWidgetItem(gameList.last().at(0), ui->gameList);
	}
}

void server::on_streamButton_clicked()
{
	startGame(ui->gameList->currentRow());
	startRDP();
	sendRequest(Request::STREAM_STARTED);
}

void server::on_configButton_clicked()
{
	cWindow = new ConnectWindow(this, settings);

	connect(cWindow, &ConnectWindow::gotInfo, [this] (QString host, int port)
	{
		remoteAddress = host;
		remotePort = port;
	});
}
