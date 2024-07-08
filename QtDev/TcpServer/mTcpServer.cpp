#include "mTcpServer.h"


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

void mConnectRun::run() {
    QByteArray inBuffer;
    if (!socketdescriptor) return;

    QTcpSocket mSocket;
    mSocket.setSocketDescriptor(socketdescriptor);
    if (mSocket.isOpen()) {
        mSocket.write("This is from server");
        mSocket.waitForBytesWritten();
        mSocket.flush();
        // loop for sending and receiving messages
        while (mSocket.waitForReadyRead()) {
            inBuffer = mSocket.readAll();
            qInfo() << socketdescriptor << ": " << inBuffer;
            // break loop when receive "quit"
            if (!strcmp(inBuffer, "quit", 4)) {
                break;
            }
            // print out message replied
            mSocket.write("Server Reply: ");
            mSocket.write(inBuffer);
            mSocket.waitForBytesWritten();
            mSocket.flush();
        }
        // close socket before return
        mSocket.close();
    }
}
