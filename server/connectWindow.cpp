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

	emit gotInfo(host, port);

	settings->setValue("host", host);
	settings->setValue("port", port);

	this->close();
}
