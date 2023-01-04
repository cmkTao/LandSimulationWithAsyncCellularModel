#include "dialog.h"

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);
    ca = new CA(0, "E:/project/c/qt_project/test_demo/dg_demo/ca_config.json");
    connect(ca, SIGNAL(isDone()), this, SLOT(slot_done()));
    connect(ca, SIGNAL(sendMessage(QString)), this, SLOT(slot_recvMessage(QString)));
}

Dialog::~Dialog() { delete ui; }

void Dialog::on_pushButton_clicked() { ca->start(); }

void Dialog::slot_done() { qDebug() << "DONE....."; }

void Dialog::slot_recvMessage(QString msg) { ui->textEdit->append(msg); }

void Dialog::on_pushButton_2_clicked() { ca->setStopFlag(true); }
