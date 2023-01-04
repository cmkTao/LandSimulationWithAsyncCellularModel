#include "IMAGE.h"
#pragma execution_character_set("utf-8")
IMAGE::IMAGE(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);
    poDataest = NULL;
    file      = "";
    init_tran();
    counter_    = false;
    image_color = false;
    treeview    = new QStandardItemModel;
    tableview   = new QStandardItemModel;
    tableview->setColumnCount(2);
    ui.graphicsView->setMouseTracking(true);  //鼠标移动事件
    connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(open_image()));
    connect(ui.actionGRAY, SIGNAL(triggered()), this, SLOT(rgb2gray()));
    connect(ui.actionVDVI, SIGNAL(triggered()), this, SLOT(cal_VDVI()));
    connect(ui.actionLaplace, SIGNAL(triggered()), this, SLOT(open_Laplace()));
    connect(ui.actionImage_linear_enhancement, SIGNAL(triggered()), this, SLOT(open_image_linear_enhancement()));
    connect(ui.actionHistogram_equalization, SIGNAL(triggered()), this, SLOT(Histogram_equalization()));
    connect(ui.actionRegion_growing, SIGNAL(triggered()), this, SLOT(open_dialog_region_grwoing()));
    connect(ui.actionGuassian, SIGNAL(triggered()), this, SLOT(open_gaussian()));
}

void IMAGE::init_tran() {
    for (int i = 0; i < 6; i++) {
        tranform[i] = 0;
    }
}
void IMAGE::init_label() {
    ui.imagex->setText(QString::number(0));
    ui.imagey->setText(QString::number(0));
    ui.prox->setText(QString::number(0));
    ui.proy->setText(QString::number(0));
}
void IMAGE::showband(GDALRasterBand *image_band) {
    if (image_band == NULL) {
        return;
    }
    vector<GDALRasterBand *> vec_bands;
    vec_bands.push_back(image_band);
    vec_bands.push_back(image_band);
    vec_bands.push_back(image_band);

    showimage(&vec_bands);
}
void IMAGE::showimage(vector<GDALRasterBand *> *imgBand) {
    if (imgBand->size() != 3) {
        return;
    }
    int imgwidth  = imgBand->at(0)->GetXSize();
    int imgheight = imgBand->at(0)->GetYSize();

    img_scale_height = 1;

    int new_scale_width  = int(imgwidth * img_scale_height - 1);
    int new_scale_height = int(imgheight * img_scale_height - 1);

    int new_size = new_scale_height * new_scale_width;

    float *rband = new float[new_size];
    float *gband = new float[new_size];
    float *bband = new float[new_size];

    unsigned char *Rband, *Gband, *Bband;

    if (image_color) {
        imgBand->at(0)->RasterIO(
            GF_Read, 0, 0, imgwidth, imgheight, rband, new_scale_width, new_scale_height, GDT_Float32, 0, 0);
        imgBand->at(1)->RasterIO(
            GF_Read, 0, 0, imgwidth, imgheight, gband, new_scale_width, new_scale_height, GDT_Float32, 0, 0);
        imgBand->at(2)->RasterIO(
            GF_Read, 0, 0, imgwidth, imgheight, bband, new_scale_width, new_scale_height, GDT_Float32, 0, 0);
        Rband = imgsketch(rband, imgBand->at(0), new_size);
        Gband = imgsketch(gband, imgBand->at(0), new_size);
        Bband = imgsketch(bband, imgBand->at(0), new_size);
    } else {
        imgBand->at(0)->RasterIO(
            GF_Read, 0, 0, imgwidth, imgheight, rband, new_scale_width, new_scale_height, GDT_Float32, 0, 0);
        Rband = imgsketch(rband, imgBand->at(0), new_size);
        Gband = Rband;
        Bband = Rband;
    }

    int            bytePerLine = (new_scale_width * 24 + 31) / 8;
    unsigned char *allBandUC   = new unsigned char[bytePerLine * new_scale_height];
    for (int h = 0; h < new_scale_height; h++) {
        for (int w = 0; w < new_scale_width; w++) {
            allBandUC[h * bytePerLine + w * 3 + 0] = Rband[h * new_scale_width + w];
            allBandUC[h * bytePerLine + w * 3 + 1] = Gband[h * new_scale_width + w];
            allBandUC[h * bytePerLine + w * 3 + 2] = Bband[h * new_scale_width + w];
        }
    }
    QGraphicsPixmapItem *image_view = new QGraphicsPixmapItem(
        QPixmap::fromImage(QImage(allBandUC, new_scale_width, new_scale_height, bytePerLine, QImage::Format_RGB888)));
    QGraphicsScene *myScene = new QGraphicsScene();
    myScene->addItem(image_view);
    // int nwidth = ui.graphicsView->width();
    // int nheight = ui.graphicsView->height();
    // ui.graphicsView->setSceneRect(QRectF(-(nwidth / 2), -(nheight / 2), nwidth, nheight));
    ui.graphicsView->setScene(myScene);
}
void IMAGE::show_tableview() {
    int rows_ = 0;
    tableview->setHorizontalHeaderLabels(QStringList() << QStringLiteral("数据类型") << QStringLiteral("数值"));
    tableview->setItem(rows_, 0, new QStandardItem(tr("Description")));
    tableview->setItem(rows_++, 1, new QStandardItem(poDataest->GetDriver()->GetDescription()));
    tableview->setItem(rows_, 0, new QStandardItem(tr("Meta Infor")));
    tableview->setItem(rows_++, 1, new QStandardItem(poDataest->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME)));
    tableview->setItem(rows_, 0, new QStandardItem(tr("Data Type")));
    tableview->setItem(
        rows_++, 1, new QStandardItem(GDALGetDataTypeName((poDataest->GetRasterBand(1)->GetRasterDataType()))));

    tableview->setItem(rows_, 0, new QStandardItem(tr("X Size")));
    tableview->setItem(rows_++, 1, new QStandardItem(QString::number(poDataest->GetRasterXSize())));
    tableview->setItem(rows_, 0, new QStandardItem(tr("Y Size")));
    tableview->setItem(rows_++, 1, new QStandardItem(QString::number(poDataest->GetRasterYSize())));
    tableview->setItem(rows_, 0, new QStandardItem(tr("Bands Size")));
    tableview->setItem(rows_++, 1, new QStandardItem(QString::number(poDataest->GetRasterCount())));

    int depth = GDALGetDataTypeSize(poDataest->GetRasterBand(1)->GetRasterDataType()) / 8;  //图像深度
    tableview->setItem(rows_, 0, new QStandardItem(tr("depth")));
    tableview->setItem(rows_++, 1, new QStandardItem(QString::number(depth)));

    tableview->setItem(rows_, 0, new QStandardItem(tr("Projection")));
    tableview->setItem(rows_++, 1, new QStandardItem(poDataest->GetProjectionRef()));

    QString origin    = "";
    QString pixelSize = "";
    double  transform_[6];
    if (poDataest->GetGeoTransform(transform_) == CE_None) {
        for (int i = 0; i < 6; i++) {
            tranform[i] = transform_[i];
        }
        origin    = QString::number(transform_[0]) + "," + QString::number(transform_[3]);
        pixelSize = QString::number(transform_[1]) + ", " + QString::number(transform_[5]);
    }
    tableview->setItem(rows_, 0, new QStandardItem(tr("Origin")));
    tableview->setItem(rows_++, 1, new QStandardItem(origin));
    tableview->setItem(rows_, 0, new QStandardItem(tr("Pixel Size")));
    tableview->setItem(rows_++, 1, new QStandardItem(pixelSize));

    tableview->setItem(rows_, 0, new QStandardItem(tr("Max Gray")));
    tableview->setItem(rows_++, 1, new QStandardItem(QString::number(image_max_grey)));
    tableview->setItem(rows_, 0, new QStandardItem(tr("Min Gray")));
    tableview->setItem(rows_++, 1, new QStandardItem(QString::number(image_min_grey)));
    ui.tableView->setModel(tableview);
}
void IMAGE::show_treeview() {
    treeview->setHorizontalHeaderLabels(QStringList() << QStringLiteral("影响名称"));
    QStandardItem *parent_ = new QStandardItem(file);
    for (int i = 0; i < poDataest->GetRasterCount(); i++) {
        QStandardItem *son_ = new QStandardItem(tr("Band %1").arg(i + 1));
        parent_->setChild(i, son_);
    }
    treeview->setItem(0, parent_);
    ui.treeView->setModel(treeview);
}
unsigned char *IMAGE::imgsketch(float *buffer, GDALRasterBand *now_band, int band_size) {
    unsigned char *new_result = new unsigned char[band_size];
    double         max_min_image[2];
    now_band->ComputeRasterMinMax(1, max_min_image);
    double min_image = max_min_image[0];
    double max_image = max_min_image[1];

    double nodata = now_band->GetNoDataValue();
    if (nodata >= min_image && nodata <= max_image) {
        min_image = 0;
    }

    for (int i = 0; i < band_size; i++) {
        if (buffer[i] == min_image) {
            new_result[i] = 0;
        } else if (buffer[i] > max_image) {
            new_result[i] = 255;
        } else {
            new_result[i] = static_cast<uchar>(((buffer[i] - min_image) / (max_image - min_image)) * 255);
        }
    }
    return new_result;
}

void IMAGE::ScaleImg(QWheelEvent *event, double factor) {
    img_scale_height *= factor;
    QMatrix matrix;
    matrix.scale(img_scale_height, img_scale_height);
    ui.graphicsView->setMatrix(matrix);
};
void IMAGE::mousePressEvent(QMouseEvent *event) {
    // 滚轮键按下，平移图像
    if (event->button() == Qt::MidButton) {
        ui.graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        ui.graphicsView->setInteractive(false);
        lastEventCursorPos = event->pos();
    }
    if (event->button() == Qt::LeftButton) {
        QPoint global_point = event->globalPos();               //获取鼠标拾取的点
        point_ = ui.graphicsView->mapFromGlobal(global_point);  //将点转化为graphicsView控件内实际的点坐标
        ui.imagex->setText(QString::number(point_.x()));
        ui.imagey->setText(QString::number(point_.y()));
        if ((tranform[0] != 0 || tranform[1] != 0 || tranform[2] != 0)) {
            double Xp = tranform[0] + point_.x() * tranform[1] + point_.y() * tranform[2];
            double Yp = tranform[3] + point_.x() * tranform[4] + point_.y() * tranform[5];
            ui.prox->setText(QString::number(Xp));
            ui.proy->setText(QString::number(Yp));
        }
    }
}

void IMAGE::mouseMoveEvent(QMouseEvent *event) {
    if (ui.graphicsView->dragMode() == QGraphicsView::ScrollHandDrag) {
        QPoint delta = (event->pos() - lastEventCursorPos) / 10;
        ui.graphicsView->horizontalScrollBar()->setValue(
            ui.graphicsView->horizontalScrollBar()->value() + (isRightToLeft() ? delta.x() : -delta.x()));
        ui.graphicsView->verticalScrollBar()->setValue(ui.graphicsView->verticalScrollBar()->value() - delta.y());
        ui.graphicsView->viewport()->setCursor(Qt::ClosedHandCursor);
    }
}
void IMAGE::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::MidButton) {
        ui.graphicsView->setDragMode(QGraphicsView::NoDrag);
    }
}
void IMAGE::wheelEvent(QWheelEvent *event) {
    // 滚轮向上滑动，放大图像
    if (event->delta() > 0) {
        ZoomIn();
    }
    // 滚轮向下滑动，缩小图像
    if (event->delta() < 0) {
        ZoomOut();
    }
}
void IMAGE::add_information_coordinate(QPoint *point_, double Xp, double Yp) {
    ui.imagex->setText(QString::number(point_->x()));
    ui.imagey->setText(QString::number(point_->y()));
    ui.prox->setText(QString::number(Xp));
    ui.proy->setText(QString::number(Yp));
}

void IMAGE::receive_image_linear_enhancement_max_value(int max_value) {
    line_enhancement_max = max_value;
    if (counter_) {
        operate_image_linear_enhancement();
    }
}
void IMAGE::receive_image_linear_enhancement_min_value(int min_value) {
    line_enhancement_min = min_value;
    if (counter_) {
        operate_image_linear_enhancement();
    }
}
