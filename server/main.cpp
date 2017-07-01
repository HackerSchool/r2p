#include <QApplication>

#include "server.h"

int main(int argc, char *argv[])
{
    // https://forum.qt.io/topic/72107/save-qlist-qstringlist-using-qsettings/2
    qRegisterMetaTypeStreamOperators<QList<QStringList>>("gameList");

    QApplication a(argc, argv);

    server w;
    w.show();

    return a.exec();
}
