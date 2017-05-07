#include "ui_connectWindow.h"

#include "connectWindow.h"
#include "r2p.h"

ConnectWindow::ConnectWindow(QWidget *parent, QSettings *settings)
	: QDialog(parent)
	, ui(new Ui::ConnectWindow)
	, settings(settings)
{
	ui->setupUi(this);

	ui->host->setText(settings->value("host").toString());

	int defaultPort = settings->value("port").toInt();
	if (defaultPort == 0) defaultPort = PORT;
	ui->port->setText(QString::number(defaultPort));

	ui->user->setText(settings->value("user").toString());

	ui->pass->setText(settings->value("pass").toString());

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->show();
}

ConnectWindow::~ConnectWindow()
{
	delete ui;
}

void ConnectWindow::on_buttonBox_accepted()
{
	QString host = ui->host->text();
	int port = ui->port->text().toInt();
	QString user = ui->user->text();
	QString pass = ui->pass->text();

	emit gotInfo(host, port, user, pass);

	settings->setValue("host", host);
	settings->setValue("port", port);
	settings->setValue("user", user);
	settings->setValue("pass", pass);

	this->close();
}
