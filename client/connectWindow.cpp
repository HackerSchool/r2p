#include "ui_connectWindow.h"

#include "connectWindow.h"
#include "r2p.h"

ConnectWindow::ConnectWindow(QWidget *parent, QString *host, int *port, QSettings *settings)
	: QDialog(parent)
	, ui(new Ui::ConnectWindow)
	, host(host)
	, port(port)
	, settings(settings)
{
	ui->setupUi(this);

	int defaultPort = settings->value("port").toInt();
	if (defaultPort == 0) defaultPort = PORT;
	ui->port->setText(QString::number(defaultPort));

	ui->host->setText(settings->value("host").toString());
	ui->host->setFocus();

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->show();
}

ConnectWindow::~ConnectWindow()
{
	delete ui;
}

void ConnectWindow::on_buttonBox_accepted()
{
	*host = ui->host->text();
	*port = ui->port->text().toInt();
	settings->setValue("host", *host);
	settings->setValue("port", *port);

	this->close();
}
