#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>
#include <iostream>
#include <QComboBox>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

// global varient must be defined at .h file with extern
// then be defined at .cpp file
extern std::vector<QString> mVecs;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    static std::vector<QString> mVecs;

private slots:

//    void on_radioButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
