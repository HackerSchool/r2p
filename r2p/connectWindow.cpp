#include "ui_connectWindow.h"

#include "connectWindow.h"
#include "r2p.h"

ConnectWindow::ConnectWindow(QWidget *parent, QString *host, int *port)
	: QDialog(parent)
	, ui(new Ui::ConnectWindow)
	, host(host)
	, port(port)
{
	ui->setupUi(this);
	ui->port->setText(QString::number(PORT));
	ui->host->setFocus();
}

ConnectWindow::~ConnectWindow()
{
	delete ui;
}

void ConnectWindow::on_buttonBox_accepted()
{
	*host = ui->host->text();
	*port = ui->port->text().toInt();
	this->close();
}
