#include "duplicatecaconfigdialog.h"

#include "ui_duplicatecaconfigdialog.h"

DuplicateCaConfigDialog::DuplicateCaConfigDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::DuplicateCaConfigDialog) {
    ui->setupUi(this);
}

DuplicateCaConfigDialog::~DuplicateCaConfigDialog() { delete ui; }

void DuplicateCaConfigDialog::on_b_choseConfig_clicked() {
    QString filePath = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择配置所在目录..."), true);
    ui->le_configDir->setText(filePath);
}

void DuplicateCaConfigDialog::on_pushButton_2_clicked() {
    QString filePath = MUTILS::getFileFromDialog(this, QString::fromLocal8Bit("选择配置所在目录..."), true);
    ui->le_saveDirPath->setText(filePath);
}

void DuplicateCaConfigDialog::on_pushButton_clicked() {
    CBatchCaSimConfig *cb                  = new CBatchCaSimConfig(ui->le_configDir->text(), 0);
    QString            newConfigNamePrefix = cb->getCurConfigDirName();
    QDir               dir;  // 当前配置目录的父级目录
    if (ui->le_saveDirPath->text().trimmed() != "") {
        dir = QDir(ui->le_saveDirPath->text());
    } else {
        dir = MUTILS::getDirFromFilePath(cb->getCurDir());
    }
    QStringList newConfigNameList;
    double      caRatioOrigin = cb->getValueFromJsonByKey(cb->getCaConfigPath(), "acaRatio").toDouble();
    for (double i = ui->ds_min->value(); i < ui->ds_max->value();) {
        QString dirPath = dir.absoluteFilePath(QString("%1_%2").arg(newConfigNamePrefix).arg(i));
        QDir    newDir(dirPath);
        if (!newDir.exists()) {
            dir.mkdir(dirPath);
        }
        qDebug() << newDir.absoluteFilePath("ca_config.json");
        cb->setValueToJsonByKey("acaRatio", i);
        cb->setValueToJsonByKey("saveSimPath", newDir.absoluteFilePath("sim.tif"));
        cb->saveToOther(newDir.absoluteFilePath("ca_config.json"));
        cb->saveEvalToOther(newDir.absoluteFilePath("eval_config.json"));
        i += ui->ds_step->value();
    }
    cb->setValueToJsonByKey("acaRatio", caRatioOrigin == 0 ? 1.0 : caRatioOrigin);
    cb->resetSimPath2Config();
    QMessageBox::information(this, QString::fromLocal8Bit("运行提示"), QString::fromLocal8Bit("生成完毕"));
}
