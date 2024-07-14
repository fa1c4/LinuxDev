#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
    // access manager
    QNetworkAccessManager *mManager = new QNetworkAccessManager(this);
    // connection
    connect(mManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(replyFinished(QNetworkReply*)));
    // disconnection
    connect(mManager, SIGNAL(finished(QNetworkReply*)), mManager, SLOT(deleteLater()));
    QNetworkReply *mReply = mManager->get(QNetworkRequest(QUrl(ui->lineEdit->text())));
    mReply->waitForReadyRead(3000);
}

void MainWindow::replyFinished(QNetworkReply* mReply) {
    ui->plainTextEdit->appendPlainText(mReply->readAll());
}

void MainWindow::on_lineEdit_returnPressed()
{
    ui->plainTextEdit->clear();
    // access manager
    QNetworkAccessManager *mManager = new QNetworkAccessManager(this);
    // connection
    connect(mManager, SIGNAL(finished(QNetworkReply *)),
            this, SLOT(replyFinished(QNetworkReply*)));
    // disconnection
    connect(mManager, SIGNAL(finished(QNetworkReply*)), mManager, SLOT(deleteLater()));
    QNetworkReply *mReply = mManager->get(QNetworkRequest(QUrl(ui->lineEdit->text())));
    mReply->waitForReadyRead(3000);
}
