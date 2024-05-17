#include "mlistwidget.h"
#include "ui_mlistwidget.h"

mListWidget::mListWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mListWidget)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("QLineEdit{font-size: 16px}");
    QFont mFont = ui->listWidget->font();
    mFont.setPointSize(16); // QFont is not a pointer, so use '.' to call function in it.
    ui->listWidget->setFont(mFont);
    ui->lineEdit->setText(QDir::homePath());
}

mListWidget::~mListWidget()
{
    delete ui;
}

void mListWidget::on_pushButton_clicked()
{
    ui->listWidget->clear();
    QString currPath = ui->lineEdit->text();
    QDir mDir(currPath);
    if (mDir.exists()) {
        QFileInfoList mList = mDir.entryInfoList();
        foreach (QFileInfo mItem, mList) {
            QString mQStr = mItem.absoluteFilePath();
            if (mItem.isDir()) mQStr += "/";
            ui->listWidget->addItem(mQStr);
        }
    } else {
//        ui->listWidget->setText("Directory does not exist."); no such usage
        QMessageBox::warning(this, "WARNING", "Directory does not exist.");
    }
}

void mListWidget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->lineEdit->setText(item->text());
    this->on_pushButton_clicked();
}
