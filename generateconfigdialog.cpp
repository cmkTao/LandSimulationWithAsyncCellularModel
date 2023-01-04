#include "generateconfigdialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <qDebug>

#include "ui_generateconfigdialog.h"
#include "utils/config.h"
#include "utils/mutils.h"

GenerateConfigDialog::GenerateConfigDialog(QWidget *parent) : QDialog(parent), ui(new Ui::GenerateConfigDialog) {
    ui->setupUi(this);
}

GenerateConfigDialog::~GenerateConfigDialog() { delete ui; }

void GenerateConfigDialog::getFilePathList(int flag) {
    QString     strs;
    QStringList file_list, output_name;
    QSettings   setting("./Setting.ini", QSettings::IniFormat);
    QString     lastPath = setting.value("LastFilePath").toString();
    QStringList str_path_list
        = QFileDialog::getOpenFileNames(this, QString::fromLocal8Bit("选择配置文件"), lastPath, "*.json");
    qDebug() << str_path_list;
    int caCount = 0, annCount = 0, evalCount = 0;
    for (int i = 0; i < str_path_list.size(); i++) {
        QString str_path = str_path_list[i];
        QString fileName = MUTILS::getFileNameByPath(str_path);
        if (fileName.startsWith("ann")) {
            annCount++;
        } else if (fileName.startsWith("ca")) {
            caCount++;
        } else if (fileName.startsWith("eval")) {
            evalCount++;
        } else {
            QMessageBox::critical(nullptr, "TIPS!",
                QString::fromLocal8Bit("配置文件名以ca_xxx.json、ann_xxx.json、eval_xxx.json, 错误命名：") + str_path);
            return;
        }
    }
    if (caCount < 1) {
        QMessageBox::critical(nullptr, "TIPS!", QString::fromLocal8Bit("CA模拟配置文件至少1个"));
        return;
    }
    if (annCount != 1) {
        QMessageBox::critical(nullptr, "TIPS!", QString::fromLocal8Bit("ANN配置文件只能为1个"));
        return;
    }
    if (evalCount != 1) {
        QMessageBox::critical(nullptr, "TIPS!", QString::fromLocal8Bit("评估eval配置文件只能为1个"));
        return;
    }
    QString iniPath = flag == 1 ? DEFAULTCONFIG::DEFAULT_CONFIG1 : DEFAULTCONFIG::DEFAULT_CONFIG2;

    QFile file(iniPath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        for (QString tmp : str_path_list) {
            stream << MUTILS::getRelativeFilePath2ExeDir(tmp) << "\n";
        }
        file.close();
        QMessageBox::information(nullptr, "TIPS!", QString::fromLocal8Bit("配置文件写入成功:") + iniPath);

    } else {
        QMessageBox::critical(nullptr, "TIPS!", QString::fromLocal8Bit("配置文件打开失败:") + iniPath);
    }
}

void GenerateConfigDialog::on_pushButton_clicked() { getFilePathList(1); }

void GenerateConfigDialog::on_pushButton_2_clicked() { getFilePathList(2); }
