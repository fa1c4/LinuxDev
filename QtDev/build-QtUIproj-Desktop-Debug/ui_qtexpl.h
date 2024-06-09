/********************************************************************************
** Form generated from reading UI file 'qtexpl.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTEXPL_H
#define UI_QTEXPL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_QtExpl
{
public:
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QDialog *QtExpl)
    {
        if (QtExpl->objectName().isEmpty())
            QtExpl->setObjectName(QString::fromUtf8("QtExpl"));
        QtExpl->resize(711, 479);
        pushButton = new QPushButton(QtExpl);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(400, 400, 170, 48));
        lineEdit = new QLineEdit(QtExpl);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(80, 40, 551, 61));
        plainTextEdit = new QPlainTextEdit(QtExpl);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(80, 120, 551, 261));

        retranslateUi(QtExpl);

        QMetaObject::connectSlotsByName(QtExpl);
    } // setupUi

    void retranslateUi(QDialog *QtExpl)
    {
        QtExpl->setWindowTitle(QApplication::translate("QtExpl", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("QtExpl", "GoTo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtExpl: public Ui_QtExpl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTEXPL_H
