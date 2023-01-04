#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <utils/global.h>

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SettingsDialog *ui;
};

#endif  // SETTINGSDIALOG_H
