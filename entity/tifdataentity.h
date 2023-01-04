#ifndef TIFDATAENTITY_H
#define TIFDATAENTITY_H
#include <gdal.h>
#include <gdal_priv.h>

#include <QDebug>
#include <QMap>
#include <QMessageBox>
#include <QString>
#include <algorithm>

#include "utils/constValue.h"
#include "utils/mutils.h"

class TifDataEntity {
public:
    TifDataEntity(QString);
    ~TifDataEntity();

    QList<QList<int>> getTransitionMatrix(TifDataEntity *);

    float *        getFloatDataByBand(int band = 1);
    double *       getDoubleDataByBand(int band = 1);
    unsigned char *getByteDataByBand(int band = 1);
    double         getNoDataByBand(int band = 1);
    float *        getDiffData(TifDataEntity *, int);
    float *        getDiffOfLegalData(TifDataEntity *);  // 获取合法像元不一致的图像数据

    /**
     * @brief getBand
     * 获取某个band
     * @param band
     * @return
     */
    GDALRasterBand *getBand(int band);

    /**
     * @brief getMax
     * 获取但band最大像素值（除无效值）
     * @return
     */
    double getMax();
    /**
     * @brief getMin
     * 获取但band最小像素值（除无效值）
     * @return
     */
    double getMin();
    /**
     * @brief getSumPixels
     * 返回有效像素总数
     * @return
     */
    int getSumPixels();
    /**
     * @brief getNumOfAllPixels 获取图像大小（像元总数，包括有效和无效）
     * @return
     */
    int getNumOfAllPixels();
    int getNumOfAllBands();
    int getMaxNPixels();
    int getMinNPixels();
    int getNTypes();

    /**
     * @brief getLandCountsByLandCode
     * 根据土地编号获取对应的数量，这里编号从1开始
     * @param code 土地编号
     * @return
     */
    int getLandCountByLandCode(int code);

    /**
     * @brief getNoDataValueByBand
     * 获取无效值
     * @param band
     * @return
     */
    double getNoDataValueByBand(int band = 1);

    /**
     * @brief close
     * 关闭raster数据
     */
    void close();

    /**
     * @brief isValidLandPixels
     * 是否是有用像素
     * @param index 从0开始
     * @return
     */
    bool isValidLandPixels(int index);
    bool isValidPixels(int index);
    bool isValidPixels(int row, int col);

    double *getTransForm();
    char *  getProjectRef();
    int     getRow();
    int     getCol();
    int     getBandCounts();
    /**
     * @brief getValueByBandAndIndex
     * 获取某band某位置（一维中的位置）的值
     * @param band
     * @param index
     * @return
     */
    double getValueByBandAndIndex(int band, int index);
    double getValueByBandAndPos(int band, int row, int col);

    void setValueByBandAndIndex(int band, int index, float value);

    GDALDataType getDataType(int band = 1);

    unsigned char *getUCharData();

    QString getFilePath();

    double *getTransFromData();
    char *  getProj();

    double getMean() const;

protected:
    template <class TT>
    bool readData();
    bool saveData(QString saveTifPath = "");

private:
    void statsLandCounts();

    QString                 filePath;
    GDALDataset *           poDataset;
    QList<GDALRasterBand *> bandList;
    int                     rasterBandCount;
    int                     imgWidth;
    int                     imgHeight;
    QList<double>           noDatas;
    QList<GDALDataType>     dataTypes;
    QList<float *>          floatBandData;
    QMap<int, int>          landCounts;  // key为土地编号
    int                     sumPixels;
    int                     nTypes;
    // 像素值的最大和最小值
    double max;
    double min;
    double m_mean;
    // 像素数量的最大和最小值
    int  maxNPixels;
    int  minNpixels;
    bool isLandUse;

    // 坐标转换
    double mpGeoTransform[6];
    // 投影
    char msProjectionRef[2048];

    unsigned char *mpData;
};

#endif  // TIFDATAENTITY_H
