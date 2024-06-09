#include "filereader.h"
#include "ui_filereader.h"

FileReader::FileReader(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileReader)
{
    ui->setupUi(this);
}

FileReader::~FileReader()
{
    delete ui;
}

void FileReader::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
//    ui->lineEdit->clear(); // clear before read so error
    QString fileName = ui->lineEdit->text();
    QFile mFile(fileName);
    if (mFile.exists()){
        if (mFile.open(QFile::ReadOnly)) {
            while (!mFile.atEnd()) {
                // read text file until the end
                QString mLine = mFile.readLine();
                ui->plainTextEdit->appendPlainText(mLine);
            }
            mFile.close();
        } else {
            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText(fileName);
            ui->plainTextEdit->appendPlainText("open file error!");
        }
    } else {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(fileName);
        ui->plainTextEdit->appendPlainText("file does not exists!");
    }
}

void FileReader::on_pushButton_2_clicked()
{
    ui->plainTextEdit->clear();
    ui->lineEdit->clear();
}

void FileReader::on_pushButton_3_clicked()
{
    char mBuffer[512] = {0};
    char mPdf[32] = {0};
    int index = 0;
    ui->plainTextEdit->clear();
    QString fileName = ui->lineEdit->text();
    QFile mFile(fileName);
    if (mFile.exists()){
        if (mFile.open(QFile::ReadOnly)) {
            while (!mFile.atEnd()) {
                // read text file until the end
                memset(mBuffer, '\0', sizeof(mBuffer) + 1);
                memset(mPdf, '\0', sizeof(mPdf) + 1);
                mFile.read(mBuffer, sizeof(mBuffer));

                while (mBuffer[index] != 0x0A) index++;
                // index count for header position

                memcpy(mPdf, mBuffer, index);
                // copy pdf format header to mPdf buffer then shows out
                ui->plainTextEdit->appendPlainText(mPdf);

                break; // only shows out pdf header infomation
            }
            mFile.close();
        } else {
            ui->plainTextEdit->clear();
            ui->plainTextEdit->appendPlainText(fileName);
            ui->plainTextEdit->appendPlainText("open file error!");
        }
    } else {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(fileName);
        ui->plainTextEdit->appendPlainText("file formatt only supports pdf for now.");
    }
}
