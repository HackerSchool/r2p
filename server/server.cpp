#include "ui_server.h"

#include "server.h"

server::server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::server)
    , r2p(this, 40500)
{
    ui->setupUi(this);

	connect(&r2p, &R2P::gotReply, [](QString const reply) {
		qDebug() << "received reply" << reply;
		// TODO: use reply
	});

	connect(&r2p, &R2P::gotRequest, [](QTcpSocket *const remote, QString const request) {
		qDebug() << "received request" << request;
		// TODO: send reply
		remote->write("hello\n");
		remote->flush();

		remote->disconnectFromHost();
		remote->deleteLater();
	});
}

server::~server()
{
    delete ui;
}

void server::sendRequest(char requestType, QString payload)
{
	r2p.sendRequest(remoteAddress, remotePort, requestType, payload);
}

void server::on_addGameButton_clicked()
{
    browser = new FileBrowser(this);
    browser->show();
}

void server::on_ConnectButton_clicked()
{
    cWindow = new ConnectWindow(this);
    cWindow->show();
}
