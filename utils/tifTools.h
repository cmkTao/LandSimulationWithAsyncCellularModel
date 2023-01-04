#ifndef TIFTOOLS_H
#define TIFTOOLS_H
#include <gdal.h>
#include <gdal_priv.h>

#include "alglib/TiffDataRead.h"
#include "alglib/TiffDataWrite.h"
#include "entity/tifdataentity.h"
namespace TIFTOOLS {
// ===================================== tif文件的写入 =================================
/**
 * @brief writeTIF2File
 * 将数据写入tif文件中，将originData中的地图
 * 信息作为新的tif文件中的信息
 * @param filePath 目标文件路径
 * @param buffer 需要写入的数据
 * @param bandCount 通道数量
 * @param originData 参照
 * @return
 */
template <class T>
bool writeTIF2File(T *buffer, GDALDataType dataType, QString filePath, int bandCount, TifDataEntity *originData) {
    QByteArray   qByteArray = filePath.toUtf8();
    char *       path       = qByteArray.data();
    int          rows       = originData->getRow();
    int          cols       = originData->getCol();
    GDALDataset *poDatasetCreate;
    // register
    if (GDALGetDriverCount() == 0) {
        GDALAllRegister();
        OGRRegisterAll();
        CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    }
    GDALDriver *mpoDriver;
    // load
    mpoDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
    if (mpoDriver == NULL) {
        cout << "CGDALWrite::init : Create poDriver Failed." << endl;
        return false;
    }
    char **papszMetadata = mpoDriver->GetMetadata();
    // 路径 宽 高 band数量 数据类型 元数据
    poDatasetCreate = mpoDriver->Create(path, cols, rows, bandCount, dataType, NULL);
    if (poDatasetCreate == NULL) {
        cout << "CGDALWrite::init : Create poDataset Failed." << endl;
        return false;
    }
    qDebug() << originData->getNoDataValueByBand();
    for (int i = 0; i < bandCount; i++) {
        if (dataType == GDT_Byte) {
            poDatasetCreate->GetRasterBand(i + 1)->SetNoDataValue(255);
        } else {
            poDatasetCreate->GetRasterBand(i + 1)->SetNoDataValue(originData->getNoDataValueByBand());
        }
    }
    poDatasetCreate->SetGeoTransform(originData->getTransForm());
    poDatasetCreate->SetProjection(originData->getProjectRef());
    poDatasetCreate->RasterIO(GF_Write, 0, 0, cols, rows, buffer, cols, rows, dataType, bandCount, 0, 0, 0, 0);
    poDatasetCreate->FlushCache();
    ////release memory
    if (poDatasetCreate != NULL) {
        GDALClose(poDatasetCreate);
        poDatasetCreate = NULL;
    }
    return true;
}

template <class T>
bool writeTIF2FileV2(T *buffer, GDALDataType dataType, QString filePath, int bandCount, TifDataEntity *originData) {
    QByteArray   qByteArray = filePath.toUtf8();
    char *       path       = qByteArray.data();
    TiffDataWrite pwrite;
    bool brlt = pwrite.init(MUTILS::string2Qstring(), originData->getRow(), originData->getCol(), 1, pread->geotransform(), pread->projectionRef(),
        GDT_Byte, originData->getNoDataByBand());
    
    
    int          rows       = originData->getRow();
    int          cols       = originData->getCol();
    GDALDataset *poDatasetCreate;
    // register
    if (GDALGetDriverCount() == 0) {
        GDALAllRegister();
        OGRRegisterAll();
        CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    }
    GDALDriver *mpoDriver;
    // load
    mpoDriver = GetGDALDriverManager()->GetDriverByName("GTiff");
    if (mpoDriver == NULL) {
        cout << "CGDALWrite::init : Create poDriver Failed." << endl;
        return false;
    }
    char **papszMetadata = mpoDriver->GetMetadata();
    // 路径 宽 高 band数量 数据类型 元数据
    poDatasetCreate = mpoDriver->Create(path, cols, rows, bandCount, dataType, NULL);
    if (poDatasetCreate == NULL) {
        cout << "CGDALWrite::init : Create poDataset Failed." << endl;
        return false;
    }
    qDebug() << originData->getNoDataValueByBand();
    for (int i = 0; i < bandCount; i++) {
        if (dataType == GDT_Byte) {
            poDatasetCreate->GetRasterBand(i + 1)->SetNoDataValue(255);
        } else {
            poDatasetCreate->GetRasterBand(i + 1)->SetNoDataValue(originData->getNoDataValueByBand());
        }
    }
    poDatasetCreate->SetGeoTransform(originData->getTransForm());
    poDatasetCreate->SetProjection(originData->getProjectRef());
    poDatasetCreate->RasterIO(GF_Write, 0, 0, cols, rows, buffer, cols, rows, dataType, bandCount, 0, 0, 0, 0);
    poDatasetCreate->FlushCache();
    ////release memory
    if (poDatasetCreate != NULL) {
        GDALClose(poDatasetCreate);
        poDatasetCreate = NULL;
    }
    return true;
}

}  // namespace TIFTOOLS
#endif  // TIFTOOLS_H
