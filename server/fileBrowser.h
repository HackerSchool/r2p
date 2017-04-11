#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>

namespace Ui {
class FileBrowser;
}

class FileBrowser : public QDialog
{
    Q_OBJECT

public:
    explicit FileBrowser(QWidget *parent = 0);
    ~FileBrowser();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::FileBrowser *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
};

#endif // FILEBROWSER_H
