#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QDialog>

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QDialog
{
	Q_OBJECT

public:
	explicit ConnectWindow(QWidget *parent, QString *host, int *port);
	~ConnectWindow();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::ConnectWindow *ui;

	QString *host;
	int *port;
};

#endif // CONNECTWINDOW_H
