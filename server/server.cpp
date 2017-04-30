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

void server::on_addGameButton_clicked()
{
    qDebug() << QFileDialog::getOpenFileName();
}
