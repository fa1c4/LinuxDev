#ifndef MLISTWIDGET_H
#define MLISTWIDGET_H

#include <QDialog>
#include <QDir>
#include <QListWidget>
#include <QFont>
#include <QFileInfoList>
#include <QMessageBox>
#include <QFileInfo>
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>

// no need for QtXml/subincludes
//#include <QtXml/QDomDocument>
//#include <QtXml/QDomElement>
//#include <QtXml/QDomNode>
//#include <QtXml/QDomNodeList>

// Qt-version5.xx includes
//#include <QXmlSimpleReader>
//#include <QXmlInputSource>
//#include <QDomDocument>
//#include <QDomElement>
//#include <QDomNode>
//#include <QDomNodeList>


namespace Ui {
class mListWidget;
}

class mListWidget : public QDialog
{
    Q_OBJECT

public:
    explicit mListWidget(QWidget *parent = nullptr);
    ~mListWidget();
//    void listNodeChld(QDomElement inElem, int lv);

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::mListWidget *ui;
};

#endif // MLISTWIDGET_H
