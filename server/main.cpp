#include <QApplication>

#include "server.h"
#include "r2p.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    server w;
    w.show();

    R2PServer s;

    return a.exec();
}
