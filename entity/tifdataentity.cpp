/**
 * @projectName   qtmflus
 * @brief         存储单通道Tif
 * @author        cmk
 * @date          2020-11-04
 */
#include "tifdataentity.h"

/**
 * @brief TifDataEntity::TifDataEntity
 * @param filePath tif文件 路径
 * 注意：类中将tif的NoDataValue统一处理为long类型
 */
TifDataEntity::TifDataEntity(QString filePath_) {
    filePath = filePath_;
    GDALAllRegister();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    poDataset = (GDALDataset *)GDALOpen(filePath.toLocal8Bit().toStdString().c_str(), GA_ReadOnly);
    if (poDataset == NULL) {
        QMessageBox::critical(nullptr, "Error!", QString("Can not open file %1").arg(filePath));
        return;
    }
    // map info
    rasterBandCount = poDataset->GetRasterCount();
    imgWidth        = poDataset->GetRasterXSize();
    imgHeight       = poDataset->GetRasterYSize();
    poDataset->GetGeoTransform(mpGeoTransform);
    strcpy(msProjectionRef, poDataset->GetProjectionRef());

    for (int i = 0; i < rasterBandCount; i++) {
        float *bandData = new float[imgWidth * imgHeight];
        bandList << poDataset->GetRasterBand(i + 1);
        noDatas << bandList.at(i)->GetNoDataValue();
        dataTypes << bandList.at(i)->GetRasterDataType();
        bandList.at(i)->RasterIO(GF_Read, 0, 0, imgWidth, imgHeight, bandData, imgWidth, imgHeight, GDT_Float32, 0, 0);
        floatBandData << bandData;
    }

    switch (dataTypes.at(0)) {
        case GDT_Byte:
            readData<unsigned char>();
            break;
        case GDT_UInt16:
            readData<unsigned short>();
            break;
        case GDT_Int16:
            readData<short>();
            break;
        case GDT_UInt32:
            readData<unsigned int>();
            break;
        case GDT_Int32:
            readData<int>();
            break;
        case GDT_Float32:
            readData<float>();
            break;
        case GDT_Float64:
            readData<double>();
            break;
        default:
            cout << "CGDALRead::loadFrom : unknown data type!" << endl;
    }

    // 土地利用数据图像，统计每一类用地的数量
    if (rasterBandCount == 1) {
        isLandUse = true;
        statsLandCounts();
    } else {
        isLandUse = false;
    }
}

TifDataEntity::~TifDataEntity() {
    //    if (this->poDataset != NULL) {
    //        this->bandList.clear();
    //        this->floatBandData.clear();
    //        this->dataTypes.clear();
    //        this->landCounts.clear();
    //        this->noDatas.clear();
    //        GDALClose(this->poDataset);
    //        this->poDataset = NULL;
    //    }

    qDeleteAll(floatBandData);
    this->floatBandData.clear();
    if (poDataset != NULL) {
        GDALClose(poDataset);
        poDataset = NULL;
    }
    if (mpData != NULL) {
        delete[] mpData;
        mpData = NULL;
    }

    this->bandList.clear();

    this->dataTypes.clear();

    this->landCounts.clear();

    this->noDatas.clear();
}

/**
 * @brief TifDataEntity::getTransitionMatrix
 * 获取转移矩阵，当前对象-> tif2的转移
 * 默认只计算band1的数据
 * 两张图的noDataValue和大小要一致，以及像素值要一致
 * @param tif2
 * @return
 */
QList<QList<int>> TifDataEntity::getTransitionMatrix(TifDataEntity *tif2) {
    QList<QList<int>> res;
    // 初始化
    for (int i = min; i <= max; i++) {
        QList<int> _temp;
        for (int j = min; j <= max; j++) {
            _temp << 0;
        }
        res << _temp;
    }
    float *data2 = tif2->getFloatDataByBand(1);
    if (imgWidth != tif2->imgWidth || imgHeight != tif2->imgHeight) {
        QMessageBox::critical(nullptr, "Error!",
            QString("图片大小不一致%1 * %2 != %3 * %4")
                .arg(imgWidth)
                .arg(imgHeight)
                .arg(tif2->imgWidth)
                .arg(tif2->imgHeight));
        return res;
    }
    int    index = 0;
    int    l1, l2;
    double _t1, _t2;
    for (int i = 0; i < imgWidth * imgHeight; i++) {
        _t1 = floatBandData[index][i];
        _t2 = data2[i];
        if (!MUTILS::inRange(max, min, _t1) || !MUTILS::inRange(max, min, _t2)) {
            continue;
        }
        l1 = int(_t1);
        l2 = int(_t2);
        res[l1 - 1][l2 - 1] += 1;
    }
    return res;
}

/**
 * @brief TifDataEntity::getFloatDataByBand
 * 根据通道获取float数据，这里band从1开始计数
 * @param band
 * @return
 */
float *TifDataEntity::getFloatDataByBand(int band) {
    band = band > rasterBandCount || band <= 0 ? 1 : band;
    return floatBandData.at(band - 1);
}

double *TifDataEntity::getDoubleDataByBand(int band) {
    int     len  = getRow() * getCol();
    double *res  = new double[len];
    float * data = floatBandData.at(band - 1);
    for (int i = 0; i < len; i++) res[i] = data[i];
    return res;
}

/**
   当为土地利用数据时，获取byte类型的数据
 * @brief TifDataEntity::getByteDataByBand
 * @param band
 * @return
 */
unsigned char *TifDataEntity::getByteDataByBand(int band) {
    int            len = getNumOfAllPixels();
    unsigned char *res = new unsigned char[len];
    for (int i = 0; i < len; i++) {
        if (isValidLandPixels(i)) {
            res[i] = (unsigned char)floatBandData.at(band - 1)[i];
        } else {
            res[i] = 255;  // 默认无效值为255
        }
    }
    return res;
}

double TifDataEntity::getNoDataByBand(int band) {
    band = band > rasterBandCount || band <= 0 ? 1 : band;
    return noDatas.at(band - 1);
}

/**
 * @brief TifDataEntity::getDiffData
 * 获取两个tif图不同的地方, 不同的地方将会设置为NodataValue
 * @param tif2
 * @param code
 * 0代表全部土地类型不一样的地方，
 * >= 1表示某种土地类型不一样的地方，如tif1土地为1的地方，在tif2中是什么类型
 * @return
 */
float *TifDataEntity::getDiffData(TifDataEntity *tif2, int code) {
    float *data2     = tif2->getFloatDataByBand(1);
    float *data1     = getFloatDataByBand(1);
    float *diffData  = new float[imgWidth * imgHeight];
    double diffPixel = noDatas[0];  // 不同部分设置为无效值NoDataValue
    double _t1, _t2;
    for (int i = 0; i < imgWidth * imgHeight; i++) {
        _t1 = data1[i];
        _t2 = data2[i];
        if (!MUTILS::inRange(max, min, _t1) || !MUTILS::inRange(max, min, _t1)) {
            diffData[i] = diffPixel;
            continue;
        }
        if (code <= 0) {
            diffData[i] = data1[i] == data2[i] ? diffPixel : 1;
        } else {
            diffData[i] = data1[i] != code ? diffPixel : data2[i];
        }
    }
    return diffData;
}

float *TifDataEntity::getDiffOfLegalData(TifDataEntity *tif2) {
    float *data2     = tif2->getFloatDataByBand(1);
    float *data1     = getFloatDataByBand(1);
    float *diffData  = new float[imgWidth * imgHeight];
    double diffPixel = noDatas[0];  // 不同部分设置为无效值NoDataValue
    int    count     = 0;
    for (int i = 0; i < imgWidth * imgHeight; i++) {
        if (isValidPixels(i) && tif2->isValidPixels(i)) {  // 合法性一致设置为diffPixel
            diffData[i] = diffPixel;
        } else {
            diffData[i] = 1;
            count++;
        }
    }
    return diffData;
}

GDALRasterBand *TifDataEntity::getBand(int band) {
    assert(band <= rasterBandCount && band >= 1);
    return bandList[band - 1];
}

double TifDataEntity::getMax() {
    assert(rasterBandCount == 1);
    return this->max;
}

double TifDataEntity::getMin() {
    assert(rasterBandCount == 1);
    return this->min;
}

int TifDataEntity::getSumPixels() { return sumPixels; }

int TifDataEntity::getNumOfAllPixels() { return this->getRow() * this->getCol(); }

int TifDataEntity::getNumOfAllBands() { return this->getNumOfAllPixels() * this->rasterBandCount; }

int TifDataEntity::getMaxNPixels() { return maxNPixels; }

int TifDataEntity::getMinNPixels() { return minNpixels; }

int TifDataEntity::getNTypes() { return nTypes; }

int TifDataEntity::getBandCounts() { return this->rasterBandCount; }

double TifDataEntity::getValueByBandAndIndex(int band, int index) { return this->floatBandData.at(band)[index]; }

double TifDataEntity::getValueByBandAndPos(int band, int row, int col) {
    int index = this->getCol() * row + col;
    return this->getValueByBandAndIndex(band, index);
}

void TifDataEntity::setValueByBandAndIndex(int band, int index, float value) {
    this->floatBandData.at(band)[index] = value;
}

int TifDataEntity::getLandCountByLandCode(int code) { return landCounts[code]; }

double TifDataEntity::getNoDataValueByBand(int band) {
    assert(band <= rasterBandCount && band >= 1);
    return noDatas[band - 1];
}

void TifDataEntity::close() {
    if (poDataset != NULL) {
        bandList.clear();
        GDALClose(poDataset);
        poDataset = NULL;
    }
    if (floatBandData.size() > 0) qDeleteAll(floatBandData);
    floatBandData.clear();
    landCounts.clear();
    noDatas.clear();
    dataTypes.clear();
}

bool TifDataEntity::isValidLandPixels(int index) {
    int d = (int)floatBandData[0][index];
    return d <= max && d >= min;
}

bool TifDataEntity::isValidPixels(int index) {
    float d = floatBandData[0][index];
    //    return d != noDatas.at(0);
    //    return d <= max && d >= min && d != noDatas.at(0);
    return d <= max && d >= min;
}

bool TifDataEntity::isValidPixels(int row, int col) {
    int index = this->getRow() * col + col;
    return this->isValidPixels(index);
}

double *TifDataEntity::getTransForm() { return mpGeoTransform; }

char *TifDataEntity::getProjectRef() { return msProjectionRef; }

int TifDataEntity::getRow() { return imgHeight; }

int TifDataEntity::getCol() { return imgWidth; }

GDALDataType TifDataEntity::getDataType(int band) {
    assert(band >= 1);
    return dataTypes[band - 1];
}

unsigned char *TifDataEntity::getUCharData() { return mpData; }

QString TifDataEntity::getFilePath() { return this->filePath; }

double *TifDataEntity::getTransFromData() { return this->mpGeoTransform; }

char *TifDataEntity::getProj() { return this->msProjectionRef; }

// 保存数据到文件
bool TifDataEntity::saveData(QString saveTifPath) {
    // 默认覆盖当前tif文件
    if (saveTifPath == "") {
        saveTifPath = this->filePath;
    }
    return false;
}

/**
 * @brief TifDataEntity::statsLandCounts
 * 统计每一类土地的数量
 */
void TifDataEntity::statsLandCounts() {
    int index = 0;
    int key;
    sumPixels  = 0;
    minNpixels = 0;
    maxNPixels = 0;
    double minmax[2];
    bandList.at(0)->ComputeRasterMinMax(1, minmax);
    //    bandList.at(0)->ComputeStatistics(1, 0, NULL, NULL, &m_mean, NULL, NULL);
    //    qDebug() << m_mean;

    min    = minmax[0];
    max    = minmax[1];
    nTypes = max - min + 1;
    // 土地数量大于MAX_LAND_TYPE，表示不是土地利用图像
    if (nTypes > CVALUE::MAX_LAND_TYPE || nTypes <= 1) {
        isLandUse = false;
        return;
    }
    for (int i = 0; i < imgWidth * imgHeight; i++) {
        if (isValidLandPixels(i)) {
            if (isLandUse) {
                key             = int(floatBandData[index][i]);
                landCounts[key] = landCounts.value(key, 0) + 1;
            }
            sumPixels++;
        }
    }
    for (int tmp : landCounts) {
        minNpixels = tmp < minNpixels ? tmp : minNpixels;
        maxNPixels = tmp > maxNPixels ? tmp : maxNPixels;
    }
}

double TifDataEntity::getMean() const { return m_mean; }

template <class TT>
bool TifDataEntity::readData() {
    if (poDataset == NULL) return false;

    // new space
    size_t _sizeof;
    _sizeof = sizeof(TT);

    int mnDatalength = imgWidth * imgHeight * rasterBandCount * _sizeof;
    mpData           = new unsigned char[mnDatalength];

    // raster IO
    CPLErr _err = poDataset->RasterIO(
        GF_Read, 0, 0, imgWidth, imgHeight, mpData, imgWidth, imgHeight, dataTypes.at(0), rasterBandCount, 0, 0, 0, 0);

    if (_err != CE_None) {
        cout << "CGDALRead::readData : raster io error!" << endl;
        return false;
    }

    return true;
}
