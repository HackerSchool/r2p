#include "server.h"
#include "ui_server.h"

#include <QFileDialog>

server::server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::server)
    , r2p(this, 40500)
{
    ui->setupUi(this);
}

server::~server()
{
    delete ui;
}

void server::sendRequest(char requestType, QString payload)
{
	r2p.sendRequest(remoteAddress, remotePort, requestType, payload);
}

void server::openFileBrowser()
{
    browser = new FileBrowser(this);
    browser->show();

    qDebug() << browser->getPath();
    if(!browser->getPath().isEmpty())
    {
       ui->listWidget->addItem(browser->getPath());
    }
}

void server::on_addGameButton_clicked()
{
    openFileBrowser();
}
