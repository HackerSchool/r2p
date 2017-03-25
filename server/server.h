#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>

namespace Ui {
class server;
}

class server : public QMainWindow
{
    Q_OBJECT

public:
    explicit server(QWidget *parent = 0);
    ~server();

private slots:
    void on_quitButton_clicked();

private:
    Ui::server *ui;
};

#endif // SERVER_H
