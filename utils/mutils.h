#ifndef MUTILS_H
#define MUTILS_H
#pragma once
#include <gdal.h>
#include <gdal_priv.h>
#include <predefines.h>

#include <QAxObject>
#include <QChar>
#include <QColor>
#include <QDebug>
#include <QDesktopServices>
#include <QException>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QProcess>
#include <QRandomGenerator>
#include <QSettings>
#include <QStandardPaths>
#include <QString>
#include <QTableWidget>
#include <QTime>
#include <exception>
#include <iostream>
#include <string>
#include "utils/constValue.h"
#include "utils/appconfig.h"
using namespace std;

#define SAFE_DELETE(p) \
    { \
        if (p) { \
            delete (p); \
            (p) = NULL; \
        } \
    }
#define SAFE_DELETE_ARRAY(p) \
    { \
        if (p) { \
            delete[](p); \
            (p) = NULL; \
        } \
    }
#define SAFE_RELEASE(p) \
    { \
        if (p) { \
            (p)->Release(); \
            (p) = NULL; \
        } \
    }

class TifDataEntity;

namespace MUTILS {

// 控制整个程序使用绝对路径还是相对路径
const bool FilePathAbsolute = false;

// 控制CA模拟是否显示模拟过程
const bool showCASimulationProcessImages = true;
const bool printCASimulationProcess      = false;

// 控制是否使用本地python环境运行脚本

#ifdef QT_NO_DEBUG
const QString EXEPATH               = "./win_main/win_main.exe";
const QString LASTPATH              = "";  // 打开文件时的默认路径
const bool    useScriptWithLocalEnv = false;
#else
const QString EXEPATH = "E:/project/LUCC/software/flus_release/win_main/win_main.exe";
// const QString LASTPATH              = "D:\\litao\\learnMaterial\\ug3\\Land_simulation\\experiment\\datas";
const QString LASTPATH = "D:\\litao\\learnMaterial\\ug3\\Land_simulation\\experiment\\datas\\resample_hgs\\exp_config";
const bool    useScriptWithLocalEnv = true;
#endif
// const QString EXEPATH = "E:/project/LUCC/software/flus_release/win_main/win_main.exe";

const QString PYTHONSCRIPTPATH = "D:\\litao\\learnMaterial\\ug3\\Land_simulation\\code\\prob\\win_main.py";

unsigned char*       ImgSketch(float* buffer, GDALRasterBand* currentBand, int bandSize, double noValue);
QGraphicsPixmapItem* combineRGBBand2Img(int width, int height, unsigned char* rBandUC, unsigned char* gBandUC,
    unsigned char* bBandUC, QGraphicsPixmapItem* item = NULL);
QGraphicsPixmapItem* getColorMap(float* floatDatas, GDALRasterBand* currentBand, QMap<double, QColor> colorMap,
    bool gray = false, const QMap<int, bool> multiCodes = QMap<int, bool>(), QGraphicsPixmapItem* item = NULL);

// ====================== 颜色操作工具函数 ===================
QColor               getRandomColor();
QList<QColor>        getRandomColors(int nums);
QMap<double, QColor> getRandomColorsMap(int nums, int start = 1);
// 颜色和16进制字符串的转换
QColor  hexStr2QColor(QString hexString);
QString qColor2HexStr(QColor c);

/**
 * @brief getRangeList
 * 获取start-nums范围内数字构成的字符串列表
 * nums=3, start=1 => {"1", "2", "3"}
 * @param nums
 * @param start
 * @return
 */
QStringList getRangeList(int nums, int start = 1);

/**
 * @brief equalNoData
 * 比较一个值是否和无效值相等，作用在于有时候tif中的NoDataValue很大，c++中表示为科学计数法
 * 无法比较大小
 * @param noData
 * @param value
 * @return
 */
bool equalNoData(double noData, double value);

/**
 * @brief inRange
 * 是否min <= value <= max
 * @param max
 * @param min
 * @return
 */
bool inRange(double max, double min, double value);

QString getFileFromDialog(QWidget* parent, QString title = "open", bool isDir = false, QString suffixs = ".*",
    bool isSave = false, bool isMulti = false);

/**
 * @brief string2Qstring
 * 将QString转为string
 * @param tmp
 * @return
 */
QString string2Qstring(string tmp);

/**
 * @brief copyFromFloatArray
 * 复制一个整数数组
 * @param srcArray 源数组
 * @param len 数组长度
 * @return
 */
int* copyFromFloatArray(int* srcArray, int len);

/**
 * @brief getRandInRange
 * 获取[low, high)之间的随机整数, 默认每次随机数都不一样
 * @param high 上界（不包括）
 * @param low 下界（包括）
 * @return
 */
int    getRandIntInRange(int low, int high);
double getRandDoubleInRange(double low = 0, double high = 1);

/**
 * @brief splitN2Ranges
 * 将[0, N) 划分为seqNums段
 * 每一段范围是[s, e]，包括两端的值
 * 比如N = 1000, seqNums = 1000
 * return
 * ((0, 165), (166, 331), (332, 497), (498, 663), (664, 829), (830, 999))
 * @param N
 * @param seqNums
 * @return
 */
QList<QList<int>> splitN2Ranges(int N, int seqNums);

template <class T>
T getMax(T a, T b) {
    return a > b ? a : b;
}

template <class T>
T getMin(T a, T b) {
    return a > b ? b : a;
}

/**
 * @brief getNeiOffset
 * 获取宽度为neiWidth的邻居偏移量
 * 例子：neiWidth = 3
 * [[-1, -1], [-1, 0], [-1, 1], [0, -1], [0, 1], [1, -1], [1, 0], [1, 1]]
 * @param neiWidth
 * @return
 */
int** getNeiOffset(int neiWidth);

float getTimeDiff(QTime time);

bool isFileExist(QString fullFileName);

QString getFileNameByPath(QString filePath);

QString getRelativeFilePath2ExeDir(QString filePath);

/**
 * @brief initPythonEnv、
 * 如果直接调用本地的python脚本文件
 * 需要为 QProcess初始化python运行环境
 * 该函数会返回python.exe的路径
 * @param p
 */
QString initPythonEnv(QProcess* p);

QString genRandomFileName(QString prefix = "", QString suffix = ".tif");
/**
 * @brief getDirFromFilePath 获取文件所在的目录
 * @param filePath
 * @return
 */
QDir getDirFromFilePath(QString filePath);

/* 安全删除 */
void saveDelete(char*);
void saveDelete(int*);
void saveDelete(int**);
void saveDelete(float*);
void saveDelete(float**);
void saveDelete(double*);
void saveDelete(double**);

/**
 * @brief truncateDouble 保留指定小数位数
 * @param value
 * @param num 指定的小数位数
 */
double truncateDouble(double value, int num);

void table2ExcelByHtml(QTableWidget* table, QString title, QString excelPath);

QStringList getSubDirName(QString dirPath);
}  // namespace MUTILS

#endif  // MUTILS_H
