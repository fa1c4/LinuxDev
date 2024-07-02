#include "mlistwidget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mListWidget mlistw;
    mlistw.show();

    return a.exec();
}
