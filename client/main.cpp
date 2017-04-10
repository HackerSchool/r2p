#include <QApplication>

#include "client.h"
#include "r2p.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client w;
    w.show();

	R2PClient c;

    return a.exec();
}
