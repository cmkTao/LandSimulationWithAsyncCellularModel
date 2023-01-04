#ifndef MAPWIDGET_H
#define MAPWIDGET_H
#include <gdal.h>
#include <gdal_priv.h>
#include <predefines.h>

#include <QColor>
#include <QDebug>
#include <QGraphicsView>
#include <QMap>
#include <QPointer>
#include <QStandardItem>

#include "utils/mutils.h"

class MyScene : public QGraphicsScene {
    Q_OBJECT
public:
    MyScene();
    ~MyScene();

    // QGraphicsScene interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class MapWidget : public QGraphicsView {
    Q_OBJECT
public:
    MapWidget(QWidget *parent);
    ~MapWidget();
    void Init();
    void FreeCurrentImgData();
    void setMapAndUpdate(QGraphicsPixmapItem *item);
    void addText(QString text);
    void ReadImg(const QString imgPath);
    void CloseCurrentImg();
    /// <summary>
    /// 返回图像元数据信息模型.
    /// </summary>
    ///< returns>图像元数据信息模型.</returns>
    QStandardItemModel *ImgMetaModel() { return imgMetaModel; };
    /// <summary>
    /// 设置图像元数据信息模型
    /// </summary>
    /// <paramname="model">图像元数据信息模型.</param>
    void SetMetaModel(QStandardItemModel *model) { this->imgMetaModel = model; };
    /// <summary>
    /// 返回文件列表数据模型
    /// </summary>
    ///< returns>文件列表数据模型.</returns>
    QStandardItemModel *FileListModel() { return fileListModel; };
    /// <summary>
    /// 设置fileListModel图像文件列表数据模型
    /// </summary>
    /// <paramname="model">文件列表数据模型.</param>
    void SetFileListModel(QStandardItemModel *model) { this->fileListModel = model; };

    QMap<double, QColor> getColorMap();
    void                 setColorMap(QMap<double, QColor> colorMap);

    /**
     * @brief showLandColorMap
     * 展示彩色的土地利用图像
     * @param landCode 显示的土地
     * 0表示显示所有土地类型，> 1表示显示某种土地类型
     * @return
     */
    bool showLandColorMap(const QMap<int, bool> multiCodes = QMap<int, bool>());

    /**
     * @brief combineRGBBand
     * 将三个通道组合起来, 生成图像
     * @param width 图像的宽
     * @param height 图像的高
     * @param rBand 红色通道
     * @param gBand 绿色通道
     * @param bBand 蓝色通道
     * @return
     */
    QGraphicsPixmapItem *combineRGBBand2Img(
        int width, int height, unsigned char *rBandUC, unsigned char *gBandUC, unsigned char *bBandUC);

    QSize sizeHint() const;

    int getRasterBandCount();

    bool getIsLandMap();

    /**
     * @brief showRGBByBands
     * @param band1 通道1
     * @param band2 通道2
     * @param band3 通道3
     */
    void showRGBByBands(int band1, int band2, int band3);

    QMap<int, int> getLandCounts();

    double getNoDataValue();

    void saveImage(QString imgPath, int width, int height);

public slots:
    /// <summary>
    /// 放大图像
    /// </summary>
    void ZoomIn() { ScaleImg(1.2); };
    /// <summary>
    /// 缩小图像
    /// </summary>
    void ZoomOut() { ScaleImg(0.8); };

protected:
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    bool isLandMap;

private:
    void           ShowBand(GDALRasterBand *band);
    void           ShowImg(QList<GDALRasterBand *> *imgBand);
    void           ShowImgInfor(const QString filename);
    void           ShowFileList(const QString filename);
    unsigned char *ImgSketch(float *buffer, GDALRasterBand *currentBand, int size, double noValue);

    /// <summary>
    /// 图像缩放
    /// </summary>
    /// <paramname="factor">缩放因子</param>
    void ScaleImg(double factor) {
        m_scaleFactor *= factor;
        QMatrix matrix;
        matrix.scale(m_scaleFactor, m_scaleFactor);
        this->setMatrix(matrix);
    };

    /// <summary>
    /// 图像元数据模型
    /// </summary>
    QStandardItemModel *imgMetaModel;
    /// <summary>
    /// 图像数据集
    /// </summary>
    GDALDataset *poDataset;

    /// <summary>
    /// 文件列表数据模型
    /// </summary>
    QStandardItemModel *fileListModel;

    // 土地颜色数据模型
    QStandardItemModel *LandColorModel;

    /// <summary>
    /// 缩放系数
    /// </summary>
    float m_scaleFactor;

    /// <summary>
    /// 判断是否显示RGB彩色图像
    /// </summary>
    bool m_showColor;



    /// <summary>
    /// 上一个鼠标事件触发时鼠标的位置
    /// </summary>
    QPoint lastEventCursorPos;

    /**
     * @brief rasterBandCount
     *  栅格图像的band数量
     */
    int rasterBandCount;
    //    QGraphicsScene *myScene;
    MyScene *myScene;

    QMap<double, QColor> colorMap;
    QMap<int, int>       landCounts;
    double               min, max;
    QList<GDALRasterBand*>  m_displayBandList;
    QList<GDALRasterBand*>  m_displayMultiBandList;
};

#endif  // MAPWIDGET_H
