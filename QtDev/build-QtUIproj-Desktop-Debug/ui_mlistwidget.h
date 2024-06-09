/********************************************************************************
** Form generated from reading UI file 'mlistwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MLISTWIDGET_H
#define UI_MLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_mListWidget
{
public:
    QLineEdit *lineEdit;
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *mListWidget)
    {
        if (mListWidget->objectName().isEmpty())
            mListWidget->setObjectName(QString::fromUtf8("mListWidget"));
        mListWidget->resize(1117, 821);
        lineEdit = new QLineEdit(mListWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 50, 811, 111));
        listWidget = new QListWidget(mListWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(140, 180, 811, 521));
        pushButton = new QPushButton(mListWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(680, 720, 231, 71));

        retranslateUi(mListWidget);

        QMetaObject::connectSlotsByName(mListWidget);
    } // setupUi

    void retranslateUi(QDialog *mListWidget)
    {
        mListWidget->setWindowTitle(QApplication::translate("mListWidget", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("mListWidget", "Go To", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mListWidget: public Ui_mListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MLISTWIDGET_H
