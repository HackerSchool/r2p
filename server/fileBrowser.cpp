#include "fileBrowser.h"
#include <string>
#include <iostream>
#include "ui_filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileBrowser)

{
    ui->setupUi(this);
    this->setWindowTitle("Add Game");

    QString sPath = "C:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dirmodel->setRootPath(sPath);
    ui->treeView->setModel(dirmodel);

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    filemodel->setRootPath(sPath);

    ui->listView->setModel(filemodel);


}


FileBrowser::~FileBrowser()
{
    delete ui;
}

void FileBrowser::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));
}

void FileBrowser::on_listView_clicked(const QModelIndex &index)
{
    // ui->listView->currentIndex().data(Qt::DisplayRole).toString();

    //Gets Path for file selected
    QModelIndex indexFile = ui->listView->selectionModel()->currentIndex();
    pathForFile = filemodel->filePath(indexFile);
    qDebug() << pathForFile;

}

QString FileBrowser::getPath()
{
    return pathForFile;
}

