#include "mapwidget.h"

#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QMouseEvent>
#include <QScrollBar>
#include <QWheelEvent>

MapWidget::MapWidget(QWidget* parent) : QGraphicsView(parent) {
    fileListModel  = new QStandardItemModel;
    imgMetaModel   = new QStandardItemModel;
    LandColorModel = new QStandardItemModel;
    imgMetaModel->setColumnCount(2);
    isLandMap     = false;
    m_scaleFactor = 1.0;
    m_showColor   = true;
    poDataset     = NULL;
    //    myScene       = new QGraphicsScene();
    myScene = new MyScene();
}

MapWidget::~MapWidget()
{
}

void MapWidget::Init()
{
    fileListModel  = new QStandardItemModel;
    imgMetaModel   = new QStandardItemModel;
    LandColorModel = new QStandardItemModel;
    imgMetaModel->setColumnCount(2);
    isLandMap     = false;
    m_scaleFactor = 1.0;
    m_showColor   = true;
    poDataset     = NULL;
    //    myScene       = new QGraphicsScene();
    myScene = new MyScene();
}

void MapWidget::FreeCurrentImgData()
{

}

void MapWidget::setMapAndUpdate(QGraphicsPixmapItem* item) {
    myScene->clear();
    myScene->addItem(item);
    this->setScene(myScene);
    this->viewport()->repaint();
}

void MapWidget::addText(QString text) { myScene->addItem(new QGraphicsSimpleTextItem(text)); }

///< summary>
///显示图像基本信息
///</summary>
///< param name="filename">文件名</param>
void MapWidget::ShowImgInfor(const QString filename) {
    if (filename == "" || poDataset == NULL) {
        return;
    }
    int row = 0;  // 用来记录数据模型的行号

    // 图像的格式信息
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("Description")));
    imgMetaModel->setItem(row++, 1, new QStandardItem(poDataset->GetDriver()->GetDescription()));
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("Meta Infor")));
    imgMetaModel->setItem(row++, 1, new QStandardItem(poDataset->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME)));
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("Data Type")));
    imgMetaModel->setItem(
        row++, 1, new QStandardItem(GDALGetDataTypeName((poDataset->GetRasterBand(1)->GetRasterDataType()))));

    // 图像的大小和波段个数
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("X Size")));
    imgMetaModel->setItem(row++, 1, new QStandardItem(QString::number(poDataset->GetRasterXSize())));
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("Y Size")));
    imgMetaModel->setItem(row++, 1, new QStandardItem(QString::number(poDataset->GetRasterYSize())));
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("Band Count")));
    imgMetaModel->setItem(row++, 1, new QStandardItem(QString::number(poDataset->GetRasterCount())));

    // 图像的投影信息
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("Projection")));
    imgMetaModel->setItem(row++, 1, new QStandardItem(poDataset->GetProjectionRef()));

    // 图像的坐标和分辨率信息
    double  adfGeoTransform[6];
    QString origin    = "";
    QString pixelSize = "";
    if (poDataset->GetGeoTransform(adfGeoTransform) == CE_None) {
        origin    = QString::number(adfGeoTransform[0]) + ", " + QString::number(adfGeoTransform[3]);
        pixelSize = QString::number(adfGeoTransform[1]) + ", " + QString::number(adfGeoTransform[5]);
    }
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("Origin")));
    imgMetaModel->setItem(row++, 1, new QStandardItem(origin));
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("Pixel Size")));
    imgMetaModel->setItem(row++, 1, new QStandardItem(pixelSize));
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("band 1 NoDataValue")));
    QString NoDataValue = QString::number(poDataset->GetRasterBand(1)->GetNoDataValue());
    imgMetaModel->setItem(row++, 1, new QStandardItem(NoDataValue));
    // 一定要通过这种方式获取最大最小值
    double* minMax = new double[2]{0};
    poDataset->GetRasterBand(1)->ComputeRasterMinMax(1, minMax);
    qDebug() << minMax[0] << minMax[1];
    imgMetaModel->setItem(row, 0, new QStandardItem(tr("max")));
    QString maxStr = QString::number(minMax[1]);
    imgMetaModel->setItem(row++, 1, new QStandardItem(maxStr));

    imgMetaModel->setItem(row, 0, new QStandardItem(tr("min")));
    QString minStr = QString::number(minMax[0]);
    imgMetaModel->setItem(row++, 1, new QStandardItem(minStr));
}

///< summary>
///显示文件结构树
///</summary>
///< param name="filename">文件名</param>
void MapWidget::ShowFileList(const QString filename) {
    if (filename == "" || poDataset == NULL) {
        return;
    }
    QFileInfo      fileInfo(filename);
    QStandardItem* rootItem = new QStandardItem(fileInfo.fileName());
    for (int i = 0; i < poDataset->GetRasterCount(); i++) {
        QStandardItem* childItem = new QStandardItem(tr("Band %1").arg(i + 1));
        rootItem->setChild(i, childItem);
    }
    fileListModel->setItem(0, rootItem);
}

///< summary>
/// 读取图像文件
///</summary>
///< param name="imgPath">图像文件</param>
void MapWidget::ReadImg(const QString imgPath) {
    GDALAllRegister();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    poDataset = (GDALDataset*)GDALOpen(imgPath.toLocal8Bit().toStdString().c_str(), GA_ReadOnly);
    if (poDataset == NULL) {
        QMessageBox::critical(this, tr("Error!"), tr("Can not open file %1").arg(imgPath));
        return;
    }
    ShowFileList(imgPath);
    ShowImgInfor(imgPath);
    rasterBandCount = poDataset->GetRasterCount();
    if (showLandColorMap()) {
        isLandMap = true;
        return;
    } else {
        isLandMap = false;
    }

    // 如果图像文件并非三个波段，则默认只显示第一波段灰度图像
    if (poDataset->GetRasterCount() < 3) {
        m_showColor = false;
//        for (auto b: m_displayBandList) {
//            SAFE_DELETE(b);
//        }
//        m_displayBandList.clear();
//        m_displayBandList.append(poDataset->GetRasterBand(1));
//        m_displayBandList.append(poDataset->GetRasterBand(1));
//        m_displayBandList.append(poDataset->GetRasterBand(1));
//        ShowImg(&m_displayBandList);
        ShowBand(poDataset->GetRasterBand(1));
    }
    // 如果图像正好三个波段，则默认以RGB的顺序显示彩色图
    else {
        m_showColor = true;
        QList<GDALRasterBand*> bandList;
        bandList.append(poDataset->GetRasterBand(1));
        bandList.append(poDataset->GetRasterBand(2));
        bandList.append(poDataset->GetRasterBand(3));
        ShowImg(&bandList);
//        for (auto b: m_displayBandList) {
//            SAFE_DELETE(b);
//        }
//        qDeleteAll(m_displayMultiBandList);
//        m_displayMultiBandList.clear();
//        m_displayMultiBandList.append(poDataset->GetRasterBand(1));
//        m_displayMultiBandList.append(poDataset->GetRasterBand(2));
//        m_displayMultiBandList.append(poDataset->GetRasterBand(3));
//        ShowImg(&m_displayMultiBandList);
    }

}

///< summary>
///显示单波段图像
///</summary>
///< param name="band">图像波段</param>
void MapWidget::ShowBand(GDALRasterBand* band) {
    if (band == NULL) {
        return;
    }

    QList<GDALRasterBand*> myBand;
    myBand.append(band);
    myBand.append(band);
    myBand.append(band);

    ShowImg(&myBand);
}

///< summary>
/// 显示图像
///</summary>
///< param name="imgBand">图像波段</param>
void MapWidget::ShowImg(QList<GDALRasterBand*>* imgBand) {
    if (imgBand->size() != 3) {
        return;
    }

    int imgWidth  = imgBand->at(0)->GetXSize();
    int imgHeight = imgBand->at(0)->GetYSize();
    //    m_scaleFactor = this->height() * 1.0 / imgHeight;
    m_scaleFactor = 1.0;

    int iScaleWidth  = (int)(imgWidth * m_scaleFactor);
    int iScaleHeight = (int)(imgHeight * m_scaleFactor);

    GDALDataType dataType = imgBand->at(0)->GetRasterDataType();

    // 首先分别读取RGB三个波段
    float* rBand = new float[iScaleWidth * iScaleHeight];
    float* gBand = new float[iScaleWidth * iScaleHeight];
    float* bBand = new float[iScaleWidth * iScaleHeight];

    unsigned char *rBandUC, *gBandUC, *bBandUC;
    // 根据是否显示彩色图像，判断RGB三个波段的组成方式，并分别读取
    if (m_showColor == true) {
        imgBand->at(0)->RasterIO(
            GF_Read, 0, 0, imgWidth, imgHeight, rBand, iScaleWidth, iScaleHeight, GDT_Float32, 0, 0);
        imgBand->at(1)->RasterIO(
            GF_Read, 0, 0, imgWidth, imgHeight, gBand, iScaleWidth, iScaleHeight, GDT_Float32, 0, 0);
        imgBand->at(2)->RasterIO(
            GF_Read, 0, 0, imgWidth, imgHeight, bBand, iScaleWidth, iScaleHeight, GDT_Float32, 0, 0);

        // 分别拉伸每个波段并将Float转换为unsigned char
        rBandUC = ImgSketch(rBand, imgBand->at(0), iScaleWidth * iScaleHeight, imgBand->at(0)->GetNoDataValue());
        gBandUC = ImgSketch(gBand, imgBand->at(1), iScaleWidth * iScaleHeight, imgBand->at(1)->GetNoDataValue());
        bBandUC = ImgSketch(bBand, imgBand->at(2), iScaleWidth * iScaleHeight, imgBand->at(2)->GetNoDataValue());
    } else {
        imgBand->at(0)->RasterIO(
            GF_Read, 0, 0, imgWidth, imgHeight, rBand, iScaleWidth, iScaleHeight, GDT_Float32, 0, 0);

        rBandUC = ImgSketch(rBand, imgBand->at(0), iScaleWidth * iScaleHeight, imgBand->at(0)->GetNoDataValue());
        gBandUC = rBandUC;
        bBandUC = rBandUC;
    }

    // 将三个波段组合起来
    //    int            bytePerLine = (iScaleWidth * 24 + 31) / 8;
    //    unsigned char* allBandUC   = new unsigned char[bytePerLine * iScaleHeight * 3];
    //    for (int h = 0; h < iScaleHeight; h++) {
    //        for (int w = 0; w < iScaleWidth; w++) {
    //            allBandUC[h * bytePerLine + w * 3 + 0] = rBandUC[h * iScaleWidth + w];
    //            allBandUC[h * bytePerLine + w * 3 + 1] = gBandUC[h * iScaleWidth + w];
    //            allBandUC[h * bytePerLine + w * 3 + 2] = bBandUC[h * iScaleWidth + w];
    //        }
    //    }
    // 构造图像并显示
    QGraphicsPixmapItem* imgItem = combineRGBBand2Img(iScaleWidth, iScaleHeight, rBandUC, gBandUC, bBandUC);
    myScene->clear();
    myScene->addItem(imgItem);
    this->setScene(myScene);
    this->viewport()->repaint();

    delete[] rBand;
    delete[] gBand;
    delete[] bBand;
}

///< summary>
/// 图像线性拉伸
///</summary>
///< param name="buffer">图像缓存</param>
///< param name="currentBand">当前波段</param>
///< param name="size">The size.</param>
///< param name="noValue">图像中的异常值</param>
///< returns>经过拉伸的8位图像缓存</returns>
unsigned char* MapWidget::ImgSketch(float* buffer, GDALRasterBand* currentBand, int bandSize, double noValue) {
    unsigned char* resBuffer = new unsigned char[bandSize];
    double         max, min, _temp;
    double         minmax[2];

    currentBand->ComputeRasterMinMax(1, minmax);
    min = minmax[0];
    max = minmax[1];
    if (min <= noValue && noValue <= max) {
        min = 0;
    }
    for (int i = 0; i < bandSize; i++) {
        _temp = buffer[i];
        if (_temp > max || _temp == noValue) {
            resBuffer[i] = 255;
        } else if (buffer[i] <= max && buffer[i] >= min) {
            resBuffer[i] = static_cast<uchar>(255 - 255 * (max - buffer[i]) / (max - min));
        } else {
            resBuffer[i] = 0;
        }
    }

    return resBuffer;
}

bool MapWidget::showLandColorMap(QMap<int, bool> multiCodes) {
    if (poDataset == NULL || rasterBandCount != 1) {
        return false;
    }
    GDALRasterBand* currentBand = poDataset->GetRasterBand(1);
    double          minmax[2];
    currentBand->ComputeRasterMinMax(1, minmax);
    min                = minmax[0];
    max                = minmax[1];
    double NoDataValue = currentBand->GetNoDataValue();
    int    diff        = (int)max - (int)min;
    // 土地类型不能超过 限制20
    if (diff > CONSTANTVALUE::MAX_LAND_COUNT || diff <= 1) {
        return false;
    }

    // 默认为随机颜色
    if (colorMap.size() < max) {
        for (int i = min; i <= max; i++) {
            colorMap[i] = QColor(rand() % 256, rand() % 256, rand() % 256);
        }
    }

    // 无效值白色
    colorMap[NoDataValue] = colorMap.value(NoDataValue, QColor(255, 255, 255));
    qDebug() << colorMap;
    int imgWidth  = currentBand->GetXSize();
    int imgHeight = currentBand->GetYSize();
    //    m_scaleFactor = this->height() * 1.0 / imgHeight;
    m_scaleFactor               = 1.0;
    int            iScaleWidth  = (int)(imgWidth * m_scaleFactor);
    int            iScaleHeight = (int)(imgHeight * m_scaleFactor);
    unsigned char* rBandUC      = new unsigned char[iScaleWidth * iScaleHeight];
    unsigned char* gBandUC      = new unsigned char[iScaleWidth * iScaleHeight];
    unsigned char* bBandUC      = new unsigned char[iScaleWidth * iScaleHeight];
    float*         bandData     = new float[iScaleWidth * iScaleHeight];
    currentBand->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, bandData, iScaleWidth, iScaleHeight, GDT_Float32, 0, 0);
    QColor tempColor;
    // 设置颜色
    for (int i = 0; i < iScaleWidth * iScaleHeight; i++) {
        if (multiCodes.size() == 0 || multiCodes.value(bandData[i], true)) {
            tempColor = colorMap.value(bandData[i], colorMap[NoDataValue]);
        } else if (!multiCodes[bandData[i]]) {
            tempColor = colorMap[NoDataValue];
        }
        rBandUC[i] = static_cast<uchar>(tempColor.red());
        gBandUC[i] = static_cast<uchar>(tempColor.green());
        bBandUC[i] = static_cast<uchar>(tempColor.blue());
    }
    // 构造图像并显示
    QGraphicsPixmapItem* imgItem = combineRGBBand2Img(iScaleWidth, iScaleHeight, rBandUC, gBandUC, bBandUC);
    myScene->clear();
    myScene->addItem(imgItem);
    this->setScene(myScene);
    this->viewport()->repaint();

    delete rBandUC;
    rBandUC = NULL;
    delete gBandUC;
    gBandUC = NULL;
    delete bBandUC;
    bBandUC = NULL;
    delete bandData;
    bandData = NULL;

    return true;
}
///< summary>
/// 控件大小
///</summary>
///< returns>QSize.</returns>
QSize MapWidget::sizeHint() const { return QSize(1024, 768); }

int MapWidget::getRasterBandCount() { return rasterBandCount; }

bool MapWidget::getIsLandMap() { return isLandMap; }

void MapWidget::showRGBByBands(int band1, int band2, int band3) {
    if (poDataset == NULL) {
        QMessageBox::critical(this, tr("Error!"), tr("Can not open file"));
        return;
    }
    QList<GDALRasterBand*> bandList;
    bandList.append(poDataset->GetRasterBand(band1));
    bandList.append(poDataset->GetRasterBand(band2));
    bandList.append(poDataset->GetRasterBand(band3));
    ShowImg(&bandList);
}

QMap<int, int> MapWidget::getLandCounts() {
    if (poDataset == NULL) {
        QMessageBox::critical(this, tr("Error!"), tr("Can not open file"));
        return landCounts;
    }
    GDALRasterBand* band         = poDataset->GetRasterBand(1);
    int             width        = band->GetXSize();
    int             height       = band->GetYSize();
    int             iScaleWidth  = width;
    int             iScaleHeight = height;
    float*          bandData     = new float[iScaleWidth * iScaleHeight];
    band->RasterIO(GF_Read, 0, 0, width, height, bandData, iScaleWidth, iScaleHeight, GDT_Float32, 0, 0);
    int key;
    for (int i = 0; i < iScaleWidth * iScaleHeight; i++) {
        if (MUTILS::inRange(max, min, bandData[i])) {
            key             = int(bandData[i]);
            landCounts[key] = landCounts.value(key, 0) + 1;
        }
    }

    delete bandData;
    bandData = NULL;

    return landCounts;
}

double MapWidget::getNoDataValue() { return poDataset->GetRasterBand(1)->GetNoDataValue(); }

void MapWidget::saveImage(QString imgPath, int width, int height) {
    QImage   image(width, height, QImage::Format_RGB32);
    QPainter painter(&image);
    myScene->render(&painter);  //关键函数
    image.save(imgPath);
}

///< summary>
///鼠标滚轮事件，实现图像缩放
///</summary>
///< param name="event">滚轮事件</param>
void MapWidget::wheelEvent(QWheelEvent* event) {
    // 滚轮向上滑动，放大图像
    if (event->delta() > 0) {
        ZoomIn();
    }
    // 滚轮向下滑动，缩小图像
    if (event->delta() < 0) {
        ZoomOut();
    }
}

///< summary>
///鼠标按键按下事件
///</summary>
///< param name="event">鼠标事件.</param>
void MapWidget::mousePressEvent(QMouseEvent* event) {
    // 滚轮键按下，平移图像
    if (event->button() == Qt::MidButton) {
        this->setDragMode(QGraphicsView::ScrollHandDrag);
        this->setInteractive(false);
        lastEventCursorPos = event->pos();
    } else {
        lastEventCursorPos = event->pos();
    }
}

///< summary>
/// 鼠标移动事件
///</summary>
///< param name="event">鼠标事件</param>
void MapWidget::mouseMoveEvent(QMouseEvent* event) {
    if (this->dragMode() == QGraphicsView::ScrollHandDrag) {
        QPoint delta = (event->pos() - lastEventCursorPos) / 5;
        this->horizontalScrollBar()->setValue(
            this->horizontalScrollBar()->value() + (isRightToLeft() ? delta.x() : -delta.x()));

        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - delta.y());

        this->viewport()->setCursor(Qt::ClosedHandCursor);
    }
}

///< summary>
///鼠标按键释放事件
///</summary>
///< param name="event">鼠标事件</param>
void MapWidget::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::MidButton) {
        this->setDragMode(QGraphicsView::NoDrag);
    } else {
        this->setDragMode(QGraphicsView::NoDrag);
    }
}

///< summary>
///关闭当前图像文件
///</summary>
void MapWidget::CloseCurrentImg() {
    if (poDataset != NULL) {
        GDALClose(poDataset);
    }

    poDataset = NULL;

    imgMetaModel->clear();
    fileListModel->clear();

    delete imgMetaModel;
    imgMetaModel = NULL;

    delete LandColorModel;
    LandColorModel = NULL;

    delete fileListModel;
    fileListModel = NULL;

    myScene->clear();
    delete myScene;
    myScene = NULL;

    colorMap.clear();
    landCounts.clear();

}

QMap<double, QColor> MapWidget::getColorMap() { return colorMap; }

void MapWidget::setColorMap(QMap<double, QColor> colorMap) { this->colorMap = colorMap; }

QGraphicsPixmapItem* MapWidget::combineRGBBand2Img(
    int width, int height, unsigned char* rBandUC, unsigned char* gBandUC, unsigned char* bBandUC) {
    int            bytePerLine = (width * 24 + 31) / 8;
    unsigned char* allBandUC   = new unsigned char[bytePerLine * height * 3];
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            allBandUC[h * bytePerLine + w * 3 + 0] = rBandUC[h * width + w];
            allBandUC[h * bytePerLine + w * 3 + 1] = gBandUC[h * width + w];
            allBandUC[h * bytePerLine + w * 3 + 2] = bBandUC[h * width + w];
        }
    }
    QGraphicsPixmapItem* imgItem = new QGraphicsPixmapItem(
        QPixmap::fromImage(QImage(allBandUC, width, height, bytePerLine, QImage::Format_RGB888)));

    delete[] allBandUC;
    allBandUC = NULL;

    return imgItem;
}

MyScene::MyScene() {}

MyScene::~MyScene() {

}

void MyScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {}

void MyScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {}

void MyScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {}
