#include "mainwindow.h"
#include "ui_mainwindow.h"


//struct Member {
//   char name[256];
//   char powerlevel[256];
//   char powertype[512];
//   char gender[64];
//};

struct Member {
    QString name;
    QString powerlevel;
    QString powertype;
    QString gender;
};

// no template name 'vector' in namesapce 'std'
//std::vector<struct Member> mMems;
//std::vector<QString> mVecs;

QVector<QString> mVecs;
QVector<struct Member> mMems;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Female");
    ui->comboBox->addItem("Male");
    ui->comboBox->addItem("Asexual");
    ui->comboBox->addItem("Transfer");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// no response when click radioButton

void MainWindow::on_pushButton_clicked()
{
    struct Member mmember;
    // get the text from lineEdit
    QString mMsg = ui->lineEdit->text() + " | ";
    mmember.name = ui->lineEdit->text();

    if (ui->radioButton->isChecked()) {
        mMsg.append(ui->radioButton->text() + " | ");
        mmember.powerlevel = ui->radioButton->text();
    }

    if (ui->radioButton_2->isChecked()) {
        mMsg.append(ui->radioButton_2->text() + " | ");
        mmember.powerlevel = ui->radioButton_2->text();
    }

    if (ui->radioButton_3->isChecked()) {
        mMsg.append(ui->radioButton_3->text() + " | ");
        mmember.powerlevel = ui->radioButton_3->text();
    }

    if (ui->checkBox->isChecked()) {
        mMsg.append(ui->checkBox->text() + " | ");
        mmember.powertype.append(ui->checkBox->text() + ",");
    }

    if (ui->checkBox_2->isChecked()) {
        mMsg.append(ui->checkBox_2->text() + " | ");
        mmember.powertype.append(ui->checkBox_2->text() + ",");
    }

    if (ui->checkBox_3->isChecked()) {
        mMsg.append(ui->checkBox_3->text() + " | ");
        mmember.powertype.append(ui->checkBox_3->text() + ",");
    }

    // not empty then strip last ','
    if (!mmember.powertype.isEmpty()) {
//        member.powertype.chop(1);
        mmember.powertype = mmember.powertype.left(mmember.powertype.length() - 1);
    }

    mMsg.append("Gender: " + ui->comboBox->currentText());
    mmember.gender = ui->comboBox->currentText();

    mMsg.append(" ");
    mVecs.push_back(mMsg);
    mMems.push_back(mmember);
    // ui->plainTextEdit->setPlainText(mMsg);
    ui->plainTextEdit->setPlainText(mMsg + "ID: " + QString::number(mVecs.size()));
    ui->statusbar->showMessage("save member " + QString::number(mVecs.size()));
}

void MainWindow::on_pushButton_2_clicked()
{
    // save mMsg to userID.csv
    QFile mFile("members.csv");
    if (!mVecs.empty()) {
        if (mFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
            QTextStream out(&mFile);
            for (auto it = mVecs.begin(); it != mVecs.end(); ++it) {
                out << *it << endl;
            }
            mVecs.clear(); // refresh mVecs after saving file
            mFile.close(); // close after saving to csv file
        } else {
            ui->plainTextEdit->setPlainText("open file error.");
        }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QFile mFile("members_data.xml");
    if (!mMems.empty()) {
        // Create Document
        QDomDocument mDoc;
        QDomProcessingInstruction pi = mDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"utf-8\"");
        mDoc.appendChild(pi);

        // Add root node
        QDomElement root = mDoc.createElement("root");
        mDoc.appendChild(root);

        // Add node iterly
        for (auto it = mMems.begin(); it != mMems.end(); ++it) {
            // add name
            QDomElement member = mDoc.createElement("member");
            QDomElement name = mDoc.createElement("name");
            QDomText tName = mDoc.createTextNode(it->name);
            name.appendChild(tName);
            member.appendChild(name);

            // add powerlevel
            QDomElement powerlevel = mDoc.createElement("powerlevel");
            QDomText tpowerlevel = mDoc.createTextNode(it->powerlevel);
            powerlevel.appendChild(tpowerlevel);
            member.appendChild(powerlevel);

            // add powertype
            QDomElement powertype = mDoc.createElement("powertype");
            QDomText tpowertype = mDoc.createTextNode(it->powertype);
            powertype.appendChild(tpowertype);
            member.appendChild(powertype);

            // add gender
            QDomElement gender = mDoc.createElement("gender");
            QDomText tgender = mDoc.createTextNode(it->gender);
            gender.appendChild(tgender);
            member.appendChild(gender);

            // add memeber to root node
            root.appendChild(member);
        }

        if (mFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&mFile);
            out << mDoc.toString();
            ui->statusbar->showMessage(QString::number(mMems.size()) + " Records have been saved.");

            mMems.clear();
            mFile.flush();
            mFile.close();
        } else {
            ui->statusbar->showMessage("xml file open error!");
        }
    }
}
