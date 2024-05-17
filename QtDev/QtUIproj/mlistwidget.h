#ifndef MLISTWIDGET_H
#define MLISTWIDGET_H

#include <QDialog>
#include <QDir>
#include <QListWidget>
#include <QFont>
#include <QFileInfoList>
#include <QMessageBox>

namespace Ui {
class mListWidget;
}

class mListWidget : public QDialog
{
    Q_OBJECT

public:
    explicit mListWidget(QWidget *parent = nullptr);
    ~mListWidget();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::mListWidget *ui;
};

#endif // MLISTWIDGET_H
