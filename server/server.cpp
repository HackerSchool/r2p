#include "server.h"
#include "ui_server.h"

#include <QFileDialog>

server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
}

server::~server()
{
    delete ui;
}

void server::openFileBrowser()
{
    browser = new FileBrowser();
    browser->show();
}

void server::on_addGameButton_clicked()
{
    openFileBrowser();
}
