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

// read binary file and print as hex format
void FileReader::on_pushButton_4_clicked()
{
    ui->plainTextEdit->clear();
    QString fileName = ui->lineEdit->text();
    QFile mFile(fileName);

    char mBuffer[16];
    char hexStr[49];
    char hexTable[17] = "0123456789abcdef"; // hex characters first character is '\0'
    // char hexTable[16] = "0123456789abcdef"; // hex characters

    // if file exists then read file
    if (mFile.exists()){
        if (mFile.open(QIODevice::ReadOnly)) {
            while (!mFile.atEnd()) {
                // read binary file until the end
                // init  buffers
                // memset(mBuffer, '\0', sizeof(mBuffer) + 1);
                // memset(hexStr, '\0', sizeof(hexStr) + 1); // off-by-one vuln
                memset(mBuffer, '\0', sizeof(mBuffer));
                memset(hexStr, '\0', sizeof(hexStr));

                qint64 mPos = mFile.pos();
                qint64 mByte = mFile.read(mBuffer, sizeof(mBuffer));
                QString mLine = QString("%1").arg(mPos, 8, 16, QLatin1Char('0'));
                mLine.append(": ");

                // convert each byte to hex
                for (int i = 0; i < mByte; ++i) {
                    char mChar = mBuffer[i];
                    int mInt = int(mChar);
                    if (mInt < 0) mInt = 256 + int(mChar);
                    hexStr[i * 3] = hexTable[int(mInt / 16)];
                    hexStr[i * 3 + 1] = hexTable[mInt % 16];
                    hexStr[i * 3 + 2] = ' ';
                }
                mLine.append(QString(hexStr));
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
