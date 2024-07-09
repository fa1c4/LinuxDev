#include "mtcpserver.h"
#include "mconnectrun.h"


mTcpServer::mTcpServer(QObject *parent): QTcpServer(parent) {
    pool = new QThreadPool(this);
    pool->setMaxThreadCount(5);
}

void mTcpServer::startServer() {
    if (this->listen(QHostAddress::LocalHost, 1234)) {
        qInfo("Server Start Successfully on localhost port 1234");
    } else {
        qInfo("Server Start Failed on localhost port 1234");
    }
}

void mTcpServer::incomingConnection(qintptr handle) {
    qInfo() << "Incoming Connection Received " << handle;
    mConnectRun *task = new mConnectRun();
    task->socketdescriptor = handle;
    task->setAutoDelete(true);
    pool->start(task);
}

//mTcpServer::mTcpServer()
//{

//}
