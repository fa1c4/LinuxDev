#ifndef FILEREADER_H
#define FILEREADER_H

#include <QDialog>
#include <string.h>

namespace Ui {
class FileReader;
}

class FileReader : public QDialog
{
    Q_OBJECT

public:
    explicit FileReader(QWidget *parent = nullptr);
    ~FileReader();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::FileReader *ui;
};

#endif // FILEREADER_H
