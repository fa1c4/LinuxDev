#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <iostream>
#include <QRunnable>


class mConnectRun: public QRunnable {
public:
    mConnectRun();
    qintptr = socketdescriptor;
protected:
    void run() override;
};

class mTcpSerer: public QTcpServer {
public:
    explicit mTcpServer(QObject *parent = nullptr);
    void startServer();

signals:
protected:
    void incomingConnection(qintptr handle) override;

private:
    QThreadPool *pool;
};