#include "ui_client.h"

#include "client.h"

client::client(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::client)
	, r2p(this, 40000)
{
	ui->setupUi(this);

	connect(&r2p, &R2P::gotReply, [](QString const reply) {
		qDebug() << "received reply" << reply;
		// TODO: use reply
	});

	connect(&r2p, &R2P::gotRequest, [](QTcpSocket *const remote, QString const request) {
		qDebug() << "received request" << request;
		// TODO: send reply
	});

	// XXX tmp test
	r2p.sendRequest("127.0.0.1", 40500, Request::GET_GAME_LIST, "hrello");
}

client::~client()
{
	delete ui;
}


void client::sendRequest(char requestType, QString payload)
{
	r2p.sendRequest(remoteAddress, remotePort, requestType, payload);
}

void client::on_connectButton_clicked()
{
	cWindow = new ConnectWindow(this, &remoteAddress, &remotePort);
	cWindow->show();
	cWindow->setAttribute(Qt::WA_DeleteOnClose);
}
