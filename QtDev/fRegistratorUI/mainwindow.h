#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QComboBox>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QtXml>
#include <QDomProcessingInstruction>
#include <QString>
#include <QVector>
#include <vector>

// dont use vector, use QVector instead
// run starts must be at .cpp file
// define struct for member information, cant use QString in struct
struct Member;

//extern std::vector<QString> mVecs;
//extern std::vector<struct Member> mMems;

// global varient must be defined at .h file with extern
// then be defined at .cpp file
extern QVector<QString> mVecs;
extern QVector<struct Member> mMems;

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

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
