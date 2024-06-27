#include "mainwindow.h"
#include "ui_mainwindow.h"
//using namespace std;


std::vector<QString> mVecs;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Female");
    ui->comboBox->addItem("Male");
    ui->comboBox->addItem("Asexual");
    ui->comboBox->addItem("Transfer");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// no response when click radioButton

void MainWindow::on_pushButton_clicked()
{
    // get the text from lineEdit
    QString mMsg = ui->lineEdit->text() + " | ";
    if (ui->radioButton->isChecked()) {
        mMsg.append(ui->radioButton->text() + " | ");
    }

    if (ui->radioButton_2->isChecked()) {
        mMsg.append(ui->radioButton_2->text() + " | ");
    }

    if (ui->radioButton_3->isChecked()) {
        mMsg.append(ui->radioButton_3->text() + " | ");
    }

    if (ui->checkBox->isChecked()) {
        mMsg.append(ui->checkBox->text() + " | ");
    }

    if (ui->checkBox_2->isChecked()) {
        mMsg.append(ui->checkBox_2->text() + " | ");
    }

    if (ui->checkBox_3->isChecked()) {
        mMsg.append(ui->checkBox_3->text() + " | ");
    }

    mMsg.append("Gender: " + ui->comboBox->currentText());
    mMsg.append(" ");
    mVecs.push_back(mMsg);
    // ui->plainTextEdit->setPlainText(mMsg);
    ui->plainTextEdit->setPlainText(mMsg + "ID: " + QString::number(mVecs.size()));
}

void MainWindow::on_pushButton_2_clicked()
{
    // save mMsg to userID.csv
    QFile mFile("members.csv");
    if (!mVecs.empty()) {
        if (mFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
            QTextStream out(&mFile);
            for (auto it = mVecs.begin(); it != mVecs.end(); ++it) {
                out << *it << endl;
            }
            mVecs.clear(); // refresh mVecs after saving file
            mFile.close(); // close after saving to csv file
        } else {
            ui->plainTextEdit->setPlainText("open file error.");
        }
    }
}
