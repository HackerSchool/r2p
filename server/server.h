#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include "filebrowser.h"

namespace Ui {
class server;
}

class server : public QMainWindow
{
    Q_OBJECT

public slots:
    void openFileBrowser();

public:
    explicit server(QWidget *parent = 0);
    ~server();
private slots:
    void on_addGameButton_clicked();

private:
    Ui::server *ui;
    FileBrowser *browser;
};

#endif // SERVER_H
