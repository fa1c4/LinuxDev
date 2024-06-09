#include "mainwindow.h"
#include "qtexpl.h"
#include "mlistwidget.h"
#include "filereader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    QtExpl q;
//    q.show();
//    mListWidget mlistw;
//    mlistw.show();
    FileReader filerder;
    filerder.show();

    return a.exec();
}
