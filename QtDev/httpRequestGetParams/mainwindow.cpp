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

    QUrl mQurl(QUrl(ui->lineEdit->text()));
    QUrlQuery mQuery;
    QString strParam = ui->lineEdit_2->text();
    if (strParam.length() > 0) {
        // check valid parameters format
        if (!strParam.contains("=") || strParam.startsWith("=") || strParam.endsWith("=")) {
            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText("Parameters Usage:");
            ui->plainTextEdit->appendPlainText("key1=val1&key2=val2[&...]");
            return;
        }

        // separate parameters by '&'
        // set key=splits('=')[0], value=splits('=')[1]
        QStringList mParamsList = strParam.split("&");
        for (int i = 0; i < mParamsList.size(); ++i) {
            QString mParam = mParamsList[i];
            QStringList mParamList = mParam.split("=");
            QString tmpKey = mParamList[0];
            QString tmpVal = mParamList[1];
            mQuery.addQueryItem(tmpKey, tmpVal);
        }
    }
    mQurl.setQuery(mQuery);

    QNetworkReply *mReply = mManager->get(QNetworkRequest(mQurl));
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
