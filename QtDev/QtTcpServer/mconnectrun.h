#ifndef MCONNECTRUN_H
#define MCONNECTRUN_H
#include "mtcpserver.h"
#include <QRunnable>


class mConnectRun: public QRunnable {
public:
    mConnectRun();
    qintptr socketdescriptor;
protected:
    void run() override;
};

//class mConnectRun
//{
//public:
//    mConnectRun();
//};

#endif // MCONNECTRUN_H
