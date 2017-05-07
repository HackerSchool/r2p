#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QDialog>
#include <QSettings>

namespace Ui {
	class ConnectWindow;
}

class ConnectWindow : public QDialog
{
	Q_OBJECT

public:
	explicit ConnectWindow(QWidget *parent, QString *host, int *port, QSettings *settings);
	~ConnectWindow();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::ConnectWindow *ui;

	QString *host;
	int *port;
	QSettings *settings;
};

#endif // CONNECTWINDOW_H
