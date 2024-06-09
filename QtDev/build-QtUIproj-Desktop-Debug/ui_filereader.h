/********************************************************************************
** Form generated from reading UI file 'filereader.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEREADER_H
#define UI_FILEREADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FileReader
{
public:
    QLineEdit *lineEdit;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QDialog *FileReader)
    {
        if (FileReader->objectName().isEmpty())
            FileReader->setObjectName(QString::fromUtf8("FileReader"));
        FileReader->resize(1654, 966);
        lineEdit = new QLineEdit(FileReader);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(90, 50, 1471, 71));
        plainTextEdit = new QPlainTextEdit(FileReader);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(90, 140, 1471, 681));
        pushButton = new QPushButton(FileReader);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1160, 870, 170, 48));
        pushButton_2 = new QPushButton(FileReader);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(1380, 870, 170, 48));
        pushButton_3 = new QPushButton(FileReader);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(920, 870, 161, 51));

        retranslateUi(FileReader);

        QMetaObject::connectSlotsByName(FileReader);
    } // setupUi

    void retranslateUi(QDialog *FileReader)
    {
        FileReader->setWindowTitle(QApplication::translate("FileReader", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("FileReader", "Open", nullptr));
        pushButton_2->setText(QApplication::translate("FileReader", "Cancel", nullptr));
        pushButton_3->setText(QApplication::translate("FileReader", "Check File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FileReader: public Ui_FileReader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEREADER_H
