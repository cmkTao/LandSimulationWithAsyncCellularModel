#ifndef CADIALOG_H
#define CADIALOG_H

#include <entity/tifdataentity.h>
#include <thirdPart/json/json.h>
#include <utils/config.h>
#include <utils/constValue.h>
#include <utils/mutils.h>

#include <QDialog>
#include <QMessageBox>
#include <QProcess>
#include <QSplineSeries>
#include <QValueAxis>
#include <QtCharts>
#include <fstream>
#include <iostream>

#include "alglib/aca.h"
#include "alglib/acca_v2.h"
#include "alglib/ca.h"
#include "alglib/ca_v2.h"

#ifdef _DEBUG
//#include "vld.h"
#endif
using namespace std;
#define SAFE_DELETE(p) \
    { \
        if (p) { \
            delete (p); \
            (p) = NULL; \
        } \
    }
#define SAFE_DELETE_ARRAY(p) \
    { \
        if (p) { \
            delete[](p); \
            (p) = NULL; \
        } \
    }
#define SAFE_RELEASE(p) \
    { \
        if (p) { \
            (p)->Release(); \
            (p) = NULL; \
        } \
    }

namespace Ui {
class CADialog;
}

class CADialog : public QDialog {
    Q_OBJECT

public:
    explicit CADialog(QWidget *parent = nullptr);
    ~CADialog();

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

    void resetUI();

private slots:
    void yearChangeSlot();
    // 表格颜色单击事件
    void colorCellClicked(QTableWidgetItem *item);
    // 表格内容事件
    void slotColorTableTextChanged(int, int);
    // 表格复选框事件
    void setVisibleStatus();
    void on_btn_chConfig_clicked();

    void on_btn_saveConfig_clicked();

    void on_btn_saveOther_clicked();

    void on_btn_lu_clicked();

    void on_btn_prob_clicked();

    void on_btn_sp_clicked();

    void on_btn_start_clicked();
    // 设置TextEdit内容
    void setRes2Te();
    void slotProcessFinshed();

    void on_btn_stop_clicked();

    void on_btn_res_clicked();

    void sltTooltip(QPointF, bool);

    // UI <-- Process
    void setMSGFromThread2UI(QString);
    void setProcess2Bar(int);
    void slotSetImage(float *, GDALRasterBand *);
    void slotSetLandCounts(int *, int);

    void on_btn_pause_clicked();

    void createThread();

    void on_btn_start_clicked(bool checked);

private:
    void              initChart();
    void              initColorTable();
    void              initTable();
    void              plotCurveChart();
    QPen              getPenFromColor(QColor color, int width = 2);
    QTableWidgetItem *getUEditQWI(QString str_);
    QTableWidgetItem *getEditQWI(QString str_);

    // 删除目录中所有文件
    void updateImgInProcessSaveDir();

    void saveChart();
    void saveLogs();

    Ui::CADialog *ui;

    QList<int>           landUseDemand;
    QList<QList<double>> costMatrix;
    QList<double>        wnb;
    int                  nTypes;
    QProcess *           m_process;
    QString              pattern;
    QRegExp              rx;
    QMap<double, QColor> colorMap;
    QMap<double, QString> nameMap;
    QMap<int, bool>      isVisibleMap;

    QMap<int, QSplineSeries *> series;
    QChart *                   chart;
    QValueAxis *               axisX;
    QValueAxis *               axisY;
    int                        maxCounts;
    int *                      landCounts;
    bool                       pause;
    int                        imgWidth;
    int                        imgHeigth;
    int                        imgCount;
    QString                    imgInProcessSaveDir;
    bool                       isinitedColor;
    CA *                       caThread;
    QMap<int, QString>         landNames;
    QList<QList<int>>          landCountInProcess;
    QGraphicsPixmapItem *      imgItem;
};

#endif  // CADIALOG_H
