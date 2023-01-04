#ifndef DUPLICATECACONFIGDIALOG_H
#define DUPLICATECACONFIGDIALOG_H

#include <QDialog>
#include <QMessageBox>

#include "entity/cbatchcasimconfig.h"
#include "utils/mutils.h"

namespace Ui {
class DuplicateCaConfigDialog;
}

class DuplicateCaConfigDialog : public QDialog {
    Q_OBJECT

public:
    explicit DuplicateCaConfigDialog(QWidget *parent = nullptr);
    ~DuplicateCaConfigDialog();

private slots:
    void on_b_choseConfig_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DuplicateCaConfigDialog *ui;
};

#endif  // DUPLICATECACONFIGDIALOG_H
