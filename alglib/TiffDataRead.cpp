﻿#include "TiffDataRead.h"

#include <time.h>
#include <windows.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "TiffDataRead.h"
#include "TiffDataWrite.h"
using namespace std;

TiffDataRead::TiffDataRead(void) {
    mpoDataset = NULL;
    mpData     = NULL;
    mgDataType = GDT_Byte;
    mnRows = mnCols = mnBands = -1;
    mnDatalength              = -1;
    mpData                    = NULL;
    memset(mpGeoTransform, 0, 6 * sizeof(double));
    strcpy(msProjectionRef, "");
    strcpy(msFilename, "");
    mdInvalidValue = 0.0f;
    mnPerPixSize   = 1;
}

TiffDataRead::~TiffDataRead(void) { close(); }

void TiffDataRead::close() {
    if (mpoDataset != NULL) {
        GDALClose(mpoDataset);
        mpoDataset = NULL;
    }

    if (mpData != NULL) {
        delete[] mpData;
        mpData = NULL;
    }

    mgDataType   = GDT_Byte;
    mnDatalength = -1;
    mnRows = mnCols = mnBands = -1;
    mpData                    = NULL;
    memset(mpGeoTransform, 0, 6 * sizeof(double));
    strcpy(msProjectionRef, "");
    strcpy(msFilename, "");
    mdInvalidValue = 0.0f;
    mnPerPixSize   = 1;
}

bool TiffDataRead::isValid() {
    if (mpoDataset == NULL || mpData == NULL) {
        return false;
    }
    return true;
}

GDALDataset* TiffDataRead::poDataset() { return mpoDataset; }

size_t TiffDataRead::rows() { return mnRows; }

size_t TiffDataRead::cols() { return mnCols; }

size_t TiffDataRead::bandnum() { return mnBands; }

unsigned char* TiffDataRead::imgData() { return mpData; }

GDALDataType TiffDataRead::datatype() { return mgDataType; }

double* TiffDataRead::geotransform() { return mpGeoTransform; }

char* TiffDataRead::projectionRef() { return msProjectionRef; }

long TiffDataRead::datalength() { return mnDatalength; }

double TiffDataRead::invalidValue() { return mdInvalidValue; }

size_t TiffDataRead::perPixelSize() { return mnPerPixSize; }

char* TiffDataRead::getFileName() { return msFilename; }

bool TiffDataRead::loadFrom(const char* _filename) {
    // close fore image
    close();

    // register
    if (GDALGetDriverCount() == 0) {
        GDALAllRegister();
        CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    }

    // open image
    mpoDataset = (GDALDataset*)GDALOpenShared(_filename, GA_ReadOnly);
    // mpoDataset = (GDALDataset*)GDALOpen(_filename, GA_ReadOnly);//

    if (mpoDataset == NULL) {
        cout << "CGDALRead::loadFrom : read file error!" << endl;
        return false;
    }

    strcpy(msFilename, _filename);

    // get attribute
    mnRows         = mpoDataset->GetRasterYSize();
    mnCols         = mpoDataset->GetRasterXSize();
    mnBands        = mpoDataset->GetRasterCount();
    mgDataType     = mpoDataset->GetRasterBand(1)->GetRasterDataType();
    mdInvalidValue = mpoDataset->GetRasterBand(1)->GetNoDataValue();
    // mapinfo
    mpoDataset->GetGeoTransform(mpGeoTransform);
    strcpy(msProjectionRef, mpoDataset->GetProjectionRef());

    // get data
    bool bRlt = false;
    switch (mgDataType) {
        case GDT_Byte:
            mnPerPixSize = sizeof(unsigned char);
            bRlt         = readData<unsigned char>();
            break;
        case GDT_UInt16:
            mnPerPixSize = sizeof(unsigned short);
            bRlt         = readData<unsigned short>();
            break;
        case GDT_Int16:
            mnPerPixSize = sizeof(short);
            bRlt         = readData<short>();
            break;
        case GDT_UInt32:
            mnPerPixSize = sizeof(unsigned int);
            bRlt         = readData<unsigned int>();
            break;
        case GDT_Int32:
            mnPerPixSize = sizeof(int);
            bRlt         = readData<int>();
            break;
        case GDT_Float32:
            mnPerPixSize = sizeof(float);
            bRlt         = readData<float>();
            break;
        case GDT_Float64:
            mnPerPixSize = sizeof(double);
            bRlt         = readData<double>();
            break;
        default:
            cout << "CGDALRead::loadFrom : unknown data type!" << endl;
            close();
            return false;
    }

    if (bRlt == false) {
        cout << "CGDALRead::loadFrom : read data error!" << endl;
        close();
        return false;
    }

    return true;
}

bool TiffDataRead::convert2uchar() {
    // new space
    // get data
    bool bRlt = false;
    switch (mgDataType) {
        case GDT_Byte:
            bRlt = convertData<unsigned char>();
            break;
        case GDT_UInt16:
            bRlt = convertData<unsigned short>();
            break;
        case GDT_Int16:
            bRlt = convertData<short>();
            break;
        case GDT_UInt32:
            bRlt = convertData<unsigned int>();
            break;
        case GDT_Int32:
            bRlt = convertData<int>();
            break;
        case GDT_Float32:
            bRlt = convertData<float>();
            break;
        case GDT_Float64:
            bRlt = convertData<double>();
            break;
        default:
            cout << "CGDALRead::loadFrom : unknown data type!" << endl;
            close();
            return false;
    }

    if (bRlt == false) {
        cout << "CGDALRead::loadFrom : convert data error!" << endl;
        close();
        return false;
    }

    return true;
}
template <class TT>
bool TiffDataRead::readData() {
    if (mpoDataset == NULL) return false;

    // new space
    size_t _sizeof;
    _sizeof = sizeof(TT);

    mnDatalength = mnRows * mnCols * mnBands * _sizeof;
    mpData       = new unsigned char[mnDatalength];

    // raster IO
    CPLErr _err
        = mpoDataset->RasterIO(GF_Read, 0, 0, mnCols, mnRows, mpData, mnCols, mnRows, mgDataType, mnBands, 0, 0, 0, 0);

    if (_err != CE_None) {
        cout << "CGDALRead::readData : raster io error!" << endl;
        return false;
    }

    return true;
}

template <class TT>
bool TiffDataRead::convertData() {
    if (mpoDataset == NULL) return false;

    size_t datalen;

    datalen = mnCols * mnRows * mnBands;

    unsigned char* tmpImage = new unsigned char[datalen];

    size_t ii;
    for (ii = 0; ii < datalen; ii++) {
        TT temp = *(TT*)(mpData + ii * sizeof(TT));

        if ((temp > 0 && temp < 255) && temp != mdInvalidValue) {
            tmpImage[ii] = (unsigned char)temp;  // 有效值调整到 1~255
        } else {
            tmpImage[ii] = (unsigned char)255;  // 无效值调整到 0
        }
    }

    // new space
    delete[] mpData;

    mpData = NULL;

    mpData = tmpImage;

    mnPerPixSize = sizeof(unsigned char);

    mgDataType = GDT_Byte;

    mdInvalidValue = 0;

    return true;
}

unsigned char* TiffDataRead::read(size_t _row, size_t _col, size_t _band) {
    return &(mpData[(_band * mnRows * mnCols + _row * mnCols + _col) * mnPerPixSize]);
}

unsigned char* TiffDataRead::readL(size_t _row, size_t _col, size_t _band) {
    // if out of rect, take mirror
    if (_row < 0)
        _row = -_row;
    else if (_row >= mnRows)
        _row = mnRows - (_row - (mnRows - 1));

    if (_col < 0)
        _col = -_col;
    else if (_col >= mnCols)
        _col = mnCols - (_col - (mnCols - 1));

    return &(mpData[(_band * mnRows * mnCols + _row * mnCols + _col) * mnPerPixSize]);
}

bool TiffDataRead::loadInfo(const char* _filename) {
    // close fore image
    close();

    // register
    if (GDALGetDriverCount() == 0) {
        GDALAllRegister();
        CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    }

    // open image
    mpoDataset = (GDALDataset*)GDALOpenShared(_filename, GA_ReadOnly);

    if (mpoDataset == NULL) {
        cout << "CGDALRead::loadFrom : read file error!" << endl;
        return false;
    }

    strcpy(msFilename, _filename);

    // get attribute
    mnRows         = mpoDataset->GetRasterYSize();
    mnCols         = mpoDataset->GetRasterXSize();
    mnBands        = mpoDataset->GetRasterCount();
    mgDataType     = mpoDataset->GetRasterBand(1)->GetRasterDataType();
    mdInvalidValue = mpoDataset->GetRasterBand(1)->GetNoDataValue();

    // mapinfo
    mpoDataset->GetGeoTransform(mpGeoTransform);
    strcpy(msProjectionRef, mpoDataset->GetProjectionRef());

    return true;
}

bool TiffDataRead::loadData() {
    // get data
    bool bRlt = false;
    switch (mgDataType) {
        case GDT_Byte:
            mnPerPixSize = sizeof(unsigned char);
            bRlt         = readData<unsigned char>();
            break;
        case GDT_UInt16:
            mnPerPixSize = sizeof(unsigned short);
            bRlt         = readData<unsigned short>();
            break;
        case GDT_Int16:
            mnPerPixSize = sizeof(short);
            bRlt         = readData<short>();
            break;
        case GDT_UInt32:
            mnPerPixSize = sizeof(unsigned int);
            bRlt         = readData<unsigned int>();
            break;
        case GDT_Int32:
            mnPerPixSize = sizeof(int);
            bRlt         = readData<int>();
            break;
        case GDT_Float32:
            mnPerPixSize = sizeof(float);
            bRlt         = readData<float>();
            break;
        case GDT_Float64:
            mnPerPixSize = sizeof(double);
            bRlt         = readData<double>();
            break;
        default:
            cout << "CGDALRead::loadFrom : unknown data type!" << endl;
            close();
            return false;
    }

    if (bRlt == false) {
        cout << "CGDALRead::loadFrom : read data error!" << endl;
        close();
        return false;
    }

    return true;
}

void TiffDataRead::deleteImgData() {
    if (mpData != NULL) {
        delete[] mpData;
        mpData = NULL;
    }
}
