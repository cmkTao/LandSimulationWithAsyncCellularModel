#ifndef IMAGEDIFFDIALOG_H
#define IMAGEDIFFDIALOG_H

#include <QDialog>
#include <QtCharts>
#include <exception>

#include "entity/tifdataentity.h"
#include "thirdPart/json/json.h"
#include "utils/config.h"
#include "utils/constValue.h"
#include "utils/mutils.h"
#include "utils/qsettingtools.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class ImageDiffDialog;
}

class ImageDiffDialog : public QDialog {
    Q_OBJECT

public:
    explicit ImageDiffDialog(QWidget *parent = nullptr);
    ~ImageDiffDialog();
    void InitLandColorAndName(QString);

private slots:
    void operatingModeButtonsToggled(int, bool);
    void slotColorTableTextChanged(int, int);
    void diffTypeChoiceSlot();
    void colorCellClicked(QTableWidgetItem *item);
    void on_btn_img1_clicked();

    void on_btn_img2_clicked();

    /**
     * @brief on_btn_confirm_clicked
     * 确认按钮
     */
    void on_btn_confirm_clicked();

    /**
     * @brief sltTooltip
     * 柱状图提示
     * @param status
     * @param index
     * @param barset
     */
    void sltTooltip(bool status, int index, QBarSet *barset);

    /**
     * @brief getNewDatas
     * 响应Combox下拉框事件
     */
    void getNewDatas();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ImageDiffDialog *ui;
    void                 connectSlot();
    QString              getPathFromDialog();
    void                 initColorTable();

    /**
     * @brief getUEditQWI
     * 获取一个不可编辑的单元格，并且内容居中
     * @param str_
     * @return
     */
    QTableWidgetItem *getUEditQWI(QString str_);

    /**
     * @brief initTransTable
     * 初始化转化表格
     */
    void initTransTable();

    /**
     * @brief initTransBarChart
     * 初始化转化柱状图
     */
    void initTransBarChart();

    QString               imgPath1;
    QString               imgPath2;
    TifDataEntity *       tifImage_1;
    TifDataEntity *       tifImage_2;
    QMap<double, QColor>  colorMap;
    QMap<double, QString> nameMap;
    QList<QList<int>>     transMatrix;
    float *               datas;
    QList<QBarSet *>      setList;

    QButtonGroup *m_btnGroup;
};

#endif  // IMAGEDIFFDIALOG_H
