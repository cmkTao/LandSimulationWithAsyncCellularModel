#ifndef VALIDATIONDIALOG_H
#define VALIDATIONDIALOG_H

#include <alglib/validationthread.h>
#include <customWidget/Loading/Loading.h>
#include <thirdPart/json/json.h>
#include <utils/config.h>
#include <utils/constValue.h>
#include <utils/mutils.h>
#include "utils/appconfig.h"

#include <QDialog>
#include <QMessageBox>
#include <QProcess>
#include <fstream>
#include <iostream>
using namespace std;

namespace Ui {
class ValidationDialog;
}

class ValidationDialog : public QDialog {
    Q_OBJECT

public:
    explicit ValidationDialog(QWidget *parent = nullptr);
    ~ValidationDialog();
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

private slots:
    void slotEvalProcessFinshed(QList<QList<double>>);

    void on_btn_config_clicked();

    void on_btn_simPath_clicked();

    void on_btn_truePath_clicked();

    void on_btn_startPath_clicked();

    void on_btn_saveConfig_clicked();

    void on_btn_saveOther_clicked();

    void on_btn_cal_clicked();

    void setRes2Te();
    void slotProcessFinshed();

private:
    void                  resetUI();
    Ui::ValidationDialog *ui;

    QProcess *        m_process;
    ValidationThread *m_vt;
    QString           pattern;
    QRegExp           rx;
};

#endif  // VALIDATIONDIALOG_H
