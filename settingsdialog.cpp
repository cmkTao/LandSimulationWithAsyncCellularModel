#include "settingsdialog.h"

#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
    ui->setupUi(this);
    if (Global::useV2) {
        ui->rb_v2->setChecked(true);
    } else {
        ui->rb_v1->setChecked(true);
    }

    if (Global::useOfficialFlus) {
        ui->rb_offical->setChecked(true);
    } else {
        ui->rb_selfD->setChecked(true);
    }
    if (Global::useProbCheck)
        ui->cb_probCheck->setChecked(true);
    else
        ui->cb_probCheck->setChecked(false);
    ui->cb_changeAlphaSetMode->setChecked(Global::changeAlphaSetMode);
}

SettingsDialog::~SettingsDialog() { delete ui; }

void SettingsDialog::on_pushButton_clicked() {
    Global::useV2              = ui->rb_v2->isChecked();
    Global::useOfficialFlus    = ui->rb_offical->isChecked();
    Global::useProbCheck       = ui->cb_probCheck->isChecked();
    Global::changeAlphaSetMode = ui->cb_changeAlphaSetMode->isChecked();
    QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("保存成功"));
}
