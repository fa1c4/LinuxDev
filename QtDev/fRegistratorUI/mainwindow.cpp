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

// no response when click radioButton

void MainWindow::on_pushButton_clicked()
{
    // get the text from lineEdit
    QString mMsg = ui->lineEdit->text() + " ";
    if (ui->radioButton->isChecked()) {
        mMsg.append(ui->radioButton->text() + " ");
    }

    if (ui->radioButton_2->isChecked()) {
        mMsg.append(ui->radioButton_2->text() + " ");
    }

    if (ui->radioButton_3->isChecked()) {
        mMsg.append(ui->radioButton_3->text() + " ");
    }

    if (ui->checkBox->isChecked()) {
        mMsg.append(ui->checkBox->text() + " ");
    }

    if (ui->checkBox_2->isChecked()) {
        mMsg.append(ui->checkBox_2->text() + " ");
    }

    if (ui->checkBox_3->isChecked()) {
        mMsg.append(ui->checkBox_3->text() + " ");
    }

    ui->plainTextEdit->setPlainText(mMsg);
}
