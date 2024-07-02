#include "mlistwidget.h"
#include "ui_mlistwidget.h"

mListWidget::mListWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mListWidget)
{
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet("QLineEdit{font-size: 32px}");
    QFont mFont = ui->listWidget->font();
    mFont.setPointSize(12); // QFont is not a pointer, so use '.' to call function in it.
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
    QFileInfo mFI(currPath);
    if (mDir.exists()) {
        QFileInfoList mList = mDir.entryInfoList();
        foreach (QFileInfo mItem, mList) {
            QString mQStr = mItem.absoluteFilePath();
            if (mItem.isDir()) mQStr += "/";
            ui->listWidget->addItem(mQStr);
        }
    } else {
        if (mFI.exists() && mFI.isFile()) {
            // QMessageBox::warning(this, "WARNING", "Object is a file.");
            // do noting when it's file
        } else {
            QMessageBox::warning(this, "WARNING", "Directory does not exist.");
        }
    }
}

void mListWidget::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->lineEdit->setText(item->text());
    this->on_pushButton_clicked();
}

// open text file and read contents
void mListWidget::on_pushButton_2_clicked()
{
    QString fileName = ui->lineEdit->text();
    ui->plainTextEdit->clear();
    QFile mFile(fileName);
    if (mFile.exists()) {
        if (mFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            ui->plainTextEdit->appendPlainText(mFile.readAll());
        } else {
            QMessageBox::warning(this, "WARNING", "File cant open for reading");
        }
    } else {
        QMessageBox::warning(this, "WARNING", "File does not exist");
    }
}

// use XbelReader to parse XML file
void mListWidget::on_pushButton_3_clicked()
{
    QString fileName = ui->lineEdit->text();
    ui->plainTextEdit->clear();
    QFile mFile(fileName);
    if (mFile.exists()) {
        if (mFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QXmlStreamReader xmlReader(&mFile);
//            int mPos = 1;
//            while (xmlReader.readNextStartElement()) {
//                ui->plainTextEdit->appendPlainText(
//                            QString("%1").arg(' ', mPos, QLatin1Char(' '))
//                                + xmlReader.name() + " : " + xmlReader.text());
//                xmlReader.skipCurrentElement();
//            }
            QString xmlName, xmlText;
            int mPos = 1;
            while (!xmlReader.atEnd() && !xmlReader.hasError()) {
                QXmlStreamReader::TokenType token = xmlReader.readNext();

                switch(token) {
                    case QXmlStreamReader::StartDocument:
                        break;
                    case QXmlStreamReader::StartElement:
                        mPos += 4;
                        xmlName = xmlReader.name().toString();
                        break;
                    case QXmlStreamReader::EndElement:
                        ui->plainTextEdit->appendPlainText(
                                QString("%1").arg(' ', mPos, QLatin1Char(' '))
                                     + xmlName + " : " + xmlText);
                        mPos -= 4;
                        break;
                    case QXmlStreamReader::Characters:
                        xmlText = xmlReader.text().toString();
                        break;
                    default:
                        break;
                }
            }

            if (xmlReader.hasError()) {
                ui->plainTextEdit->appendPlainText("XML ERROR: " + xmlReader.errorString());
            }

            mFile.close();
        } else {
            QMessageBox::warning(this, "WARNING", "File cant open for reading");
        }
    } else {
        QMessageBox::warning(this, "WARNING", "File does not exist");
    }
}

/*
---- uncompatible version implementation below ----
*/

// traverse list node child
//void mListWidget::listNodeChld(QDomElement inElem, int lv) {
//    QDomNode node = inElem.firstChild();
//    int level = lv;
//    int mPos = level * 4;
//    while (!node.isNull()) {
//        QDomElement mElem = node.toElement();
//        if (!mElem.isNull()) {
//            ui->plainTextEdit->appendPlainText(
//                        QString("%1").arg(' ', mPos, QLatin1Char(' '))
//                        + mElem.tagName() + " : " + mElem.text());
//        }

//        if (mElem.hasChildNodes()) {
//            int chLevel = lv++;
//            this->listNodeChld(mElem, chLevel);
//        }
//        node = node.nextSibling();
//    }
//}

// Parser for XML file
//void mListWidget::on_pushButton_3_clicked()
//{
//    QString fileName = ui->lineEdit->text();
//    ui->plainTextEdit->clear();
//    QFile mFile(fileName);
//    if (mFile.exists()) {
//        if (mFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//            QDomDocument mDoc;
//            mDoc.setContent(&mFile);
//            QDomElement mDocElem = mDoc.documentElement();
//            QDomNode mNode = mDocElem.firstChild();

//            while (!mNode.isNull()) {
//                QDomElement nodeElem = mNode.toElement();
//                ui->plainTextEdit->appendPlainText(nodeElem.tagName());
//                if (mNode.hasChildNodes()) {
//                    this->listNodeChld(nodeElem, 1);
//                }
//                mNode = mNode.nextSibling();
//            }

//            ui->plainTextEdit->appendPlainText(mFile.readAll());
//        } else {
//            QMessageBox::warning(this, "WARNING", "File cant open for reading");
//        }
//    } else {
//        QMessageBox::warning(this, "WARNING", "File does not exist");
//    }
//}
