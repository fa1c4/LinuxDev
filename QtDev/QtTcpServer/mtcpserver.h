#ifndef MTCPSERVER_H
#define MTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <iostream>


class mTcpServer: public QTcpServer {
public:
    explicit mTcpServer(QObject *parent = nullptr);
    void startServer();

signals:
protected:
    void incomingConnection(qintptr handle) override;

private:
    QThreadPool *pool;
};

//class mTcpServer
//{
//public:
//    mTcpServer();
//};

#endif // MTCPSERVER_H
