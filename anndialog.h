#ifndef ANNDIALOG_H
#define ANNDIALOG_H

#include <thirdPart/json/json.h>
#include <utils/mutils.h>

#include "utils/appconfig.h"

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>
#include <QSettings>
#include <QTime>
#include <fstream>
#include <iostream>

using namespace std;

namespace Ui {
class ANNDialog;
}

class ANNDialog : public QDialog {
    Q_OBJECT

public:
    explicit ANNDialog(QWidget *parent = nullptr);
    ~ANNDialog();

    /**
     * @brief uI2Json
     * 将界面的配置保存到json文件中
     * @param jsonPath
     */
    void uI2Json(QString jsonPath);
    /**
     * @brief json2Ui
     * 将json文件中的内容加载到界面中
     * @param jsonPath
     */
    bool json2Ui(QString jsonPath);

    void saveTifPathToConfig();

private slots:

    void on_btn_chConfig_clicked();

    void on_btn_chDir_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_btn_chProbPath_clicked();

    void on_rb_two_toggled(bool checked);

    void on_btn_saveConfig_clicked();

    void on_btn_startSim_clicked();

    void setRes2Te();

    void on_btn_stopSim_clicked();
    void slotProcessFinshed();

private:
    void resetUI();

    Ui::ANNDialog *ui;

    QString   configPath;
    QProcess *m_process;
    QString   pattern1;
    QString   pattern2;
    QRegExp   rx1;
    QRegExp   rx2;
    int       curr_epochs;
    int       all_epochs;
    int       curr_batch;
    int       all_batch;
    QTime     time;
};

#endif  // ANNDIALOG_H
