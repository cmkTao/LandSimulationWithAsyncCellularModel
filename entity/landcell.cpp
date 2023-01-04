#include "landcell.h"

LandCell::LandCell(int row, int col, int landType) {
    this->row                = row;
    this->col                = col;
    this->landType           = landType;
    this->landTypeInLastTime = this->landType;
    this->probsInANN         = NULL;
}

LandCell::~LandCell() {
    neighborsMap.clear();
    delete[] probsInANN;
    probsInANN = NULL;
}

// 通过组合概率来选择下一轮当前像元可能的土地类型
int LandCell::allocateNewType(
    double *wnb, double *convertCost, double landInertia, int windowSize, int nTypes, bool twoYears) {
    int numOfClasses = nTypes;
    // 使用两期数据，在获取ANN概率时有偏移
    // 比如两期数据，4种土地类型，有16种变化，则土地1对应0-3，土地二对应4-7
    int     offset       = twoYears ? (this->landType - 1) * nTypes : 0;
    double *combineProbs = new double[numOfClasses];
    double *roulette     = new double[numOfClasses + 1];
    // 计算邻域影响
    double *portion  = calNeighborsProportion(numOfClasses, windowSize);
    double  sumProbs = 0;
    for (int i = 0; i < numOfClasses; ++i) {
        combineProbs[i] = probsInANN[i + offset] * (wnb[i] * portion[i]) * convertCost[i];
        //        combineProbs[i] = probsInANN[i + offset] * (wnb[i] * portion[i]) * convertCost[i];
        combineProbs[i] *= this->landType - 1 == i ? landInertia * 10 * numOfClasses : 1;
        sumProbs += combineProbs[i];
    }
    roulette[0] = 0;
    for (int i = 0; i < numOfClasses; ++i) {
        combineProbs[i] = sumProbs == 0 ? 0 : combineProbs[i] / sumProbs;
        roulette[i + 1] = roulette[i] + combineProbs[i];
    }

    /* roulette choice return a new type(start from 1)*/
    int    newType = this->landType;
    double ranData = MUTILS::getRandDoubleInRange();
    for (int i = 0; i < numOfClasses; ++i) {
        if (roulette[i + 1] >= ranData && roulette[i] < ranData) {
            newType = i + 1;
            break;
        }
    }
    // 释放空间
    delete[] combineProbs;
    combineProbs = NULL;
    delete[] roulette;
    roulette = NULL;
    delete[] portion;
    portion = NULL;
    return newType;
}

void LandCell::addOneNeighborCell(LandCell *cell) {
    //    this->neighborsMap[cell->getMkey()] = cell;
    this->neighborsMap.insert(cell->getIndex(), cell);
}

int LandCell::getLandType() { return this->landType; }

void LandCell::setLandType(int tmp) { this->landType = tmp; }

void LandCell::setLandTypeInLastTime(int tmp) { this->landTypeInLastTime = tmp; }

int LandCell::getLandTypeInLastTime() { return this->landTypeInLastTime; }

int LandCell::getRow() { return this->row; }

int LandCell::getCol() { return this->col; }

void LandCell::setIndex(int index) { this->indexIn1D = index; }

int LandCell::getIndex() { return this->indexIn1D; }

void LandCell::setProbs(double *probs) { this->probsInANN = probs; }

double *LandCell::getProbs() { return this->probsInANN; }

double LandCell::getANNProbsByType(int type, int nTypes, bool twoYears) {
    int offset = twoYears ? (this->landType - 1) * nTypes : 0;
    return probsInANN[type - 1 + offset];
}

bool LandCell::isRestricted() { return this->restricted; }

void LandCell::setRestricted(bool tmp) { this->restricted = tmp; }

double *LandCell::calNeighborsProportion(int numOfClasses, int windowSize) {
    double *portions = new double[numOfClasses];
    for (int i = 0; i < numOfClasses; i++) {
        portions[i] = 0;
    }

    // 获取邻居上一次迭代后的结果
    for (LandCell *cell : this->neighborsMap) {
        portions[cell->getLandTypeInLastTime() - 1] += 1;
    }

    for (int i = 0; i < numOfClasses; i++) {
        portions[i] /= (double)windowSize;
    }
    return portions;
}

void LandCell::setCol(int value) { col = value; }

void LandCell::setRow(int value) { row = value; }
