#ifndef CA_H
#define CA_H
#include <gdal.h>
#include <gdal_priv.h>

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QMap>
#include <QString>
#include <QTextCodec>
#include <QThread>
#include <QTime>
#include <QtConcurrent>
#include <fstream>
#include <string>

#include "alglib/TiffDataRead.h"
#include "alglib/TiffDataWrite.h"
#include "entity/landcell.h"
#include "entity/tifdataentity.h"
#include "thirdPart/json/json.h"
#include "utils/config.h"
#include "utils/constValue.h"
#include "utils/global.h"

//#ifdef _DEBUG
//#include "vld.h"
//#endif

using namespace std;

class CA : public QThread {
    Q_OBJECT
public:
    CA();
    CA(QObject *parent, QString filePath);
    ~CA();

    /**
     * @brief loadFromConfigFile
     * 通过json文件初始化配置
     * @param filePath
     */
    void loadFromConfigFile(QString filePath);

    /**
     * @brief loadTifData
     * 通过配置加载tif数据
     */
    void loadTifData();

    /**
     * @brief initAllVariables
     * 初始化所有变量，该函数调用前需要先加载所有基本配置
     */
    void initAllVariables();

    /**
     * @brief initCells
     * 初始化Cells
     */
    virtual void initCells();

    virtual void initNeiOfCells();

    virtual int     rouletteNewType(LandCell *cell, double landInertia);
    virtual double *calNeighborsProportion(LandCell *cell);

    /**
     * @brief isInRestricted
     * 判断是否是限制矩阵中的cell
     * 1表示允许转换，0表示禁止转换
     * @param index 一维中的相对下标
     * @return
     */
    bool isInRestricted(int index);

    // 执行同步模拟
    virtual void startSimulation();

    // ========= Setter And Getter
    void setLandUsePath(string tmp);
    void setProbsPath(string tmp);
    void setSaveTifPath(string tmp);
    void setRestrictedTifPath(string tmp);

    void setUsedYears(int tmp);
    void setRandomNum(int tmp);
    void setNumIternations(int tmp);
    void setNeiSize(int tmp);
    void setLandUseDemand(int *tmp);
    void setNeiIntensity(double *tmp);
    void setCostMatrix(double **tmp);
    void setDegree(int tmp);

    void setConfigPath(QString tmp);
    void setStopFlag(bool tmp);
    void setPauseFlag(bool tmp);

    void freeImgFloatData();

    void run_test();

    void printDebug();

    int endIterTimes() const;

protected:
    // QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();

signals:
    void isDone();  //处理完成信号
    void signalSendMessage(QString);
    void signalSendProcess(int);
    void signalSendLandCounts(int *, int);
    void signalSendImagData(float *, GDALRasterBand *);

protected:
    // ================ Functions =============
    // =============== 模拟的公用方法begin ==============
    void write2File(string filePath, QHash<int, LandCell *> cellMap, float *landImagData = NULL);

    /**
     * @brief scanWindow
     * 获取邻居的坐标偏移量
     * @param sizeWindows
     * @return
     */
    int **scanWindow(int sizeWindows);

    /**
     * @brief updateLandInertia
     * 更新自适应系数
     * @param iter
     */
    void updateLandInertia(int iter);

    /**
     * @brief tryToAllocate
     * 对一个cell尝试执行土地类型转换
     * @param k 当前的迭代次数
     * @param newTypeIndex 新土地类型
     * @param oldTypeIndex 旧的土地类型
     * @param cell 当前的cell单元
     */
    void tryToAllocate(int k, int newTypeIndex, int oldTypeIndex, LandCell *cell, double newTypeProb = -1.0);

    // =============== 模拟的公用方法end ==============

    // =============== 与外部通信的方法begin ==================
    // 发送 字符串消息
    void sendStringMSG(const QString msg);
    // 发送 当前土地总数量 + 当前迭代次数
    void sendLandCount(int *land_count, int key);
    // 发送 当前图像 + 土地利用tif的band1
    void sendImageData();
    // 发送 当前迭代次数
    void sendCurrentIter(int k);
    // =============== 与外部通信的方法end ====================

    void freeMemories();

    /**
     * @brief freeCellSpace 释放细胞空间
     */
    virtual void freeCellSpace();

    // --------------------------------------------------------------------------------
    // ================ Attributes =============

    bool    isToStop;
    bool    isPause;
    string  landUseTifPath;
    string  probsTifPath;
    string  saveTifPath;
    string  restrictedTifPath;
    QString configPath;

    // 记录使用的是几期数据
    int usedYears;
    int randomNum;
    int numIternations;
    // 邻域半径
    int neiSize;
    int neiWindow;  // 邻居个数
    int nTypes;
    int rows;
    int cols;
    // 邻居坐标偏移量
    int **direction;
    int * landUseDemand;

    double * neiIntensity;
    double **costMatrix;
    double   degree;

    double NoDataValue;

    bool isRestrictExit;

    // map存储Cells，key=index, value=LanCell
    QHash<int, LandCell *> cellMap;

    TifDataEntity *landUseImage;
    TifDataEntity *probImage;
    TifDataEntity *restrictImage;

    // =========== variables in simulation ==================
    int *   saveCount;
    double *mdNeiborhoodProbability;
    double *mdRoulette;
    double *probability;
    double *initialProb;
    double *adjustment_effect;
    double *adjustment;
    double *mIminDis2goal;
    double *initialDist;
    double *dynaDist;
    double *bestdis;
    double *opposite2reverse;
    int     pixelSum;
    bool    twoYears;

    float *imgFloatData;
    int    endDiffValue;
    // aca同步率
    float acaRatio;
    int   threadCount;

    int m_endIterTimes;  // 终止时运行次数

    // 是否使用官方FLUS软件逻辑
    bool m_useFLUSFOfficialVersion;

    // ----------- variables in simulation ------------------
};

#endif  // CA_H
