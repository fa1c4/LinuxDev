#include "qtexpl.h"
#include "ui_qtexpl.h"
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QFont>

QtExpl::QtExpl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QtExpl)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("QLineEdit{font-size: 18px}");
//    QFont mFont = ui->lineEdit->font();
//    mFont.setPointSize(12);
    QFont mFont = ui->plainTextEdit->font();
    mFont.setPointSize(14);
//    ui->lineEdit->setFont(mFont);
    ui->plainTextEdit->setFont(mFont);
    ui->lineEdit->setText(QDir::homePath());
}

QtExpl::~QtExpl()
{
    delete ui;
}

void QtExpl::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
    QString currPath = ui->lineEdit->text();
    QDir mDir(currPath);
    if (mDir.exists()) {
        QFileInfoList mList = mDir.entryInfoList();
        foreach (QFileInfo mItem, mList) {
            ui->plainTextEdit->appendPlainText(mItem.absoluteFilePath());
        }
    } else {
        ui->plainTextEdit->setPlainText("Directory doesn't exist.");
    }
}
