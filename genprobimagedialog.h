#ifndef GENPROBIMAGEDIALOG_H
#define GENPROBIMAGEDIALOG_H

#include <thirdPart/json/json.h>

#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <fstream>

#include "utils/mutils.h"

namespace Ui {
class GenProbImageDialog;
}

class GenProbImageDialog : public QDialog {
    Q_OBJECT

public:
    explicit GenProbImageDialog(QWidget *parent = nullptr);
    ~GenProbImageDialog();

private slots:
    void on_pushButton_clicked();
    void setRes2Te();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::GenProbImageDialog *ui;
    QProcess *              m_process;
    QString                 landUseFilePath;
    QString                 saveDir;
};

#endif  // GENPROBIMAGEDIALOG_H
