#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("QLineEdit{font-size: 32px; color: blue;}");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->lineEdit->setText("Infinit Horror World is Coming. Waiting for transportation...");
//    for (int i = 0; i < 10; i++) {
//        if (i % 5 == 1) sleep(1);
//    }
//    sleep(1);
    ui->lineEdit->setText("Welcome to Infinit Horror World, player 0xfa1c4!");
//    exit(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("Keep naive and be happy. Aborting...");
//    sleep(1);
    exit(0);
}
