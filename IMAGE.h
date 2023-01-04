#pragma once

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent >
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QPoint>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QWheelEvent>
#include <QtWidgets/QMainWindow>
#include <iostream>
#include <vector>

#include "gdal_priv.h"
#include "ui_IMAGE.h"

using namespace std;
class IMAGE : public QMainWindow {
    Q_OBJECT
public slots:
    void open_image();
    void cal_VDVI();
    void open_Laplace();
    void receive_laplace_par(QVariant var);
    void open_image_linear_enhancement();
    void receive_image_linear_enhancement_max_value(int max_value);
    void receive_image_linear_enhancement_min_value(int min_value);
    void operate_image_linear_enhancement();
    void Histogram_equalization();
    void open_dialog_region_grwoing();
    void receive_region_auto(QVariant par_auto);
    void receive_region_peo(QVariant par_peo);
    void open_gaussian();
    void receive_guassian_par(QVariant par_guassian);
signals:
    void send_line_value(int max_value, int min_value);

public:
    IMAGE(QWidget *parent = Q_NULLPTR);
    GDALDataset *poDataest;

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void           init_tran();
    void           init_label();
    void           add_information_coordinate(QPoint *point_, double Xp, double Yp);
    void           show_tableview();
    void           show_treeview();
    void           showband(GDALRasterBand *image_band);
    void           showimage(vector<GDALRasterBand *> *imgBand);
    unsigned char *imgsketch(float *buffer, GDALRasterBand *now_band, int band_size);
    void           ScaleImg(QWheelEvent *event, double factor);
    void           ZoomIn() {
        QWheelEvent *even_ = NULL;
        ScaleImg(even_, 1.2);
    };
    void ZoomOut() {
        QWheelEvent *even_ = NULL;
        ScaleImg(even_, 0.8);
    };
    QString             file;
    bool                image_color;
    Ui::IMAGEClass      ui;
    QStandardItemModel *treeview;
    QStandardItemModel *tableview;
    QImage              qimage_;
    QPoint              lastEventCursorPos;
    int                 line_enhancement_max;
    int                 line_enhancement_min;
    double              image_max_grey;
    double              image_min_grey;
    bool                counter_;
    double              tranform[6];
    float               img_scale_height;
    QPoint              point_;  //鼠标拾取的像素位置
};
