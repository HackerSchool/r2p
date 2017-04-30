#include "client.h"
#include "ui_client.h"

client::client(QWidget *parent)
	: QMainWindow(parent)
    , ui(new Ui::client)
    , r2p(this, 40000)
{
    ui->setupUi(this);

	// XXX temp test
    QString *r = new QString("127.0.0.1");
    QString *p = new QString("hello!");
    r2p.sendRequest(r, 40500, Request::GET_GAME_LIST, p);
    delete r;
    delete p;
}

client::~client()
{
    delete ui;
}

