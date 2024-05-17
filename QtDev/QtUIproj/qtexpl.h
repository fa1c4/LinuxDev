#ifndef QTEXPL_H
#define QTEXPL_H

#include <QDialog>

namespace Ui {
class QtExpl;
}

class QtExpl : public QDialog
{
    Q_OBJECT

public:
    explicit QtExpl(QWidget *parent = nullptr);
    ~QtExpl();

private slots:
    void on_pushButton_clicked();

private:
    Ui::QtExpl *ui;
};

#endif // QTEXPL_H
