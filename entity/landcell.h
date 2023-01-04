/**
 * @projectName   qtmflus
 * @brief         土地细胞
 * @author        cmk
 * @date          2020-11-11
 */

#ifndef LANDCELL_H
#define LANDCELL_H
#include <utils/mutils.h>

#include <QDebug>
#include <QList>
#include <QMap>
#include <QString>

#include "utils/constValue.h"

class LandCell {
public:
    LandCell(int row, int col, int landType);
    ~LandCell();

    /**
     * @brief allocateNewType
     * 计算组合概率，采用轮盘选，获取一个候选的新土地类型
     * @param wnb 邻域权重
     * @param probs 概率
     * @param convertCost 转换代价
     * @param landInertia 自适应系数
     * @param windowSize 邻域窗口大小
     * @return 一个新的类型(从1开始)
     */
    int allocateNewType(
        double* wnb, double* convertCost, double landInertia, int windowSize, int nTypes, bool twoYears = false);

    /**
     * @brief addOneNeighborCell
     * 添加一个邻居
     * @param cell
     */
    virtual void addOneNeighborCell(LandCell* cell);

    // ================== setter and getter================
    int  getLandType();
    void setLandType(int tmp);
    void setLandTypeInLastTime(int tmp);
    int  getLandTypeInLastTime();

    int getRow();
    int getCol();

    void setIndex(int index);
    int  getIndex();

    void    setProbs(double* probs);
    double* getProbs();

    double getANNProbsByType(int type, int nTypes, bool twoYears = false);

    bool isRestricted();
    void setRestricted(bool tmp);

    void setRow(int value);

    void setCol(int value);

protected:
    // ===================== Function ================================
    virtual double* calNeighborsProportion(int numOfClasses, int windowSize = 9);

    // ===================== Attribute ================================
    // 细胞在网格中的位置
    int row;
    int col;
    // 细胞在一维中的相对位置
    int indexIn1D;

    // 细胞当前的土地类型, 注意这里和网格中土地编号一致，从1开始
    int landType;

    int landTypeInLastTime;

    // 该cell位置处对应的probabilities
    double* probsInANN;

    // 细胞的邻居
    QMap<int, LandCell*> neighborsMap;

    // 是否是限制发展的元素
    bool restricted;
};

#endif  // LANDCELL_H
