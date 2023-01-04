#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <utils/qsettingtools.h>

#include <QColorDialog>
#include <QDialog>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QtCharts>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog {
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent = nullptr);
    ~ImageDialog();
    void readImage(QString);
    void resetUI();
    void InitLandNameAndColor(QString);

private slots:
    void showTifSlot();
    void showRGBBandByCombox();
    void colorCellClicked(QTableWidgetItem *item);
    void sltTooltip(bool status, int index, QBarSet *barset);
    /**
     * @brief showColorMapsByLandCodes
     * 响应checkbox，显示某些土地
     */
    void showColorMapsByLandCodes();

    void on_export_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ImageDialog *     ui;
    QMap<double, QColor>  colorMap;
    QMap<double, QString> nameMap;
    /**
     * @brief initColorTableView
     * 初始化表格模型
     */
    void            initColorTableView();
    void            initChartView(QMap<int, int> landCounts);
    QMap<int, bool> multiCodes;
    QString         tifFilePath;
};

#endif  // IMAGEDIALOG_H
