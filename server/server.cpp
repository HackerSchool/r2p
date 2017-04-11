#include "server.h"
#include "ui_server.h"

#include <QFileDialog>

server::server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server)
{
    ui->setupUi(this);
    connect(ui->addGameButton, SIGNAL(click()), this, SLOT(openFileBrowser()));
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
