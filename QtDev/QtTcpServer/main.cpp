#include <QCoreApplication>
#include "mconnectrun.h"
#include "mtcpserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    mTcpServer mtcpserver;
    mtcpserver.startServer();

    return a.exec();
}
