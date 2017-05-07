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
	explicit ConnectWindow(QWidget *parent, QSettings *settings);
	~ConnectWindow();

signals:
	void gotInfo(QString host, int port);

private slots:
	void on_buttonBox_accepted();

private:
	Ui::ConnectWindow *ui;

	QSettings *settings;
};

#endif // CONNECTWINDOW_H
