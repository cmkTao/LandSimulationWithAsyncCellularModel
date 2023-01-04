#ifndef GENERATECONFIGDIALOG_H
#define GENERATECONFIGDIALOG_H

#include <QDialog>

namespace Ui {
class GenerateConfigDialog;
}

class GenerateConfigDialog : public QDialog {
    Q_OBJECT

public:
    explicit GenerateConfigDialog(QWidget *parent = nullptr);
    ~GenerateConfigDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GenerateConfigDialog *ui;

    void getFilePathList(int flag);
};

#endif  // GENERATECONFIGDIALOG_H
