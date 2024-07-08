#include "mainwindow.h"
#include "ui_mainwindow.h"


QString hostIp = "127.0.0.1";
qint32 hostPort = 1234;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSocket = new QTcpSocket(this);
    connect(mSocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Connect button
void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
    mSocket->connectToHost(hostIp, hostPort);
    if (mSocket->waitForConnected(3000)) {
        ui->plainTextEdit->appendPlainText("Connection to host " + hostIp +
                                           " port " + QString::number(hostPort) + " succeed");
    } else {
        ui->plainTextEdit->appendPlainText("Connection to host " + hostIp +
                                           " port " + QString::number(hostPort) + " failed");
    }
}

// DisConnect buttion
void MainWindow::on_pushButton_2_clicked()
{
    mSocket->close();
    ui->plainTextEdit->appendPlainText("Connection to host " + hostIp +
                                       " port " + QString::number(hostPort) + " closed");
}

void MainWindow::readyRead() {
    QByteArray mBytes;
    mBytes = mSocket->readAll();
    ui->plainTextEdit->appendPlainText(QString(mBytes));
}

void MainWindow::on_lineEdit_returnPressed()
{
    char mBuffer[1024];
    if (mSocket->isWritable()) {
        QString mStr = ui->lineEdit->text();
        memset(mBuffer, '\0', sizeof(mBuffer));
        memcpy(mBuffer, mStr.toUtf8(), mStr.length());
        mSocket->write(mBuffer);
        mSocket->waitForBytesWritten(1000);
        ui->plainTextEdit->appendPlainText("Client Send: " + QString(mBuffer));
        ui->lineEdit->clear(); // clear after sending
    }
}
