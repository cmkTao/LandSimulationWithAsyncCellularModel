#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "alglib/ca.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
signals:
    void stopThread();
private slots:
    void on_pushButton_clicked();
    void slot_done();
    void slot_recvMessage(QString);

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;

    CA *ca;
};

#endif  // DIALOG_H
