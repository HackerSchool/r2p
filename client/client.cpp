#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent)
	: QMainWindow(parent)
    , ui(new Ui::client)
    , r2p(this, 40000)
{
    ui->setupUi(this);

	// XXX temp test
    r2p.sendRequest("127.0.0.1", 40500, Request::GET_GAME_LIST, "hrello");
}

client::~client()
{
    delete ui;
}

