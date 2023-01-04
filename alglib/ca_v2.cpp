#include "ca_v2.h"

CA_V2::CA_V2() {}

CA_V2::CA_V2(QObject *parent, QString filePath) : CA(parent, filePath) { m_alpha = 1.0; }

void CA_V2::startSimulation() {
    isToStop = false;
    isPause  = false;
    loadFromConfigFile(configPath);
    qDebug() << QString::fromLocal8Bit("ca_v2异步模拟%1_%2").arg(acaRatio).arg(m_useFLUSFOfficialVersion);
    m_alpha = acaRatio;
    sendStringMSG(QString::fromLocal8Bit("ca异步模拟%1").arg(acaRatio));

    initAllVariables();
    LandCell *cell = new LandCell(-1, -1, -1);
    int       newTypeIndex, oldTypeIndex;
    //    bool                                   isConvert;
    twoYears          = this->usedYears == 2;
    bool    hasWrited = false;
    QString msg;
    float * tmpStateSpace = new float[rows * cols];  // 存储临时数据
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index            = i * this->cols + j;
            imgFloatData[index]  = landUseImage->getFloatDataByBand()[index];
            tmpStateSpace[index] = landUseImage->getFloatDataByBand()[index];
            if (landUseImage->isValidLandPixels(index)) {
                m_indexList << index;
            }
        }
    }

    m_endIterTimes = 0;
    m_count        = 0;
    for (int k = 0; k < this->numIternations; ++k) {
        if (this->isPause) {
            --k;
            continue;
        }
        sendCurrentIter(k + 1);
        // ==== step1. 更新惯性系数 ====
        updateLandInertia(k);

        // step2. 执行转换
        for (int index : m_indexList) {
            // 异步
            double randAlpha = MUTILS::getRandDoubleInRange(0, 1);
            if (randAlpha > m_alpha) {
                continue;
            }

            if (isInRestricted(index)) {
                continue;
            }
            // 初始化临时细胞
            cell->setLandType(imgFloatData[index]);
            cell->setIndex(index);
            cell->setRow(index / this->cols);
            cell->setCol(index % this->cols);

            // 执行转换前保存上次迭代结果，所有变化以上一次的结果为基准
            oldTypeIndex = cell->getLandType() - 1;

            // ==== step2.1 获取一个cell候选类型 ====
            newTypeIndex = rouletteNewType(cell, adjustment_effect[oldTypeIndex]) - 1;
            // ==== step2.2 尝试从候选类型中选择一个土地类型进行转换 ====
            int offset = twoYears ? (cell->getLandType() - 1) * nTypes : 0;
            tryToAllocate(
                k, newTypeIndex, oldTypeIndex, cell, probImage->getValueByBandAndIndex(newTypeIndex + offset, index));
            tmpStateSpace[index] = cell->getLandType();  // 更新到临时数组中
        }
        if (m_count != 0) qDebug() << QString("error prob pixels=%1").arg(m_count);
        m_count = 0;
        for (int index : m_indexList) {
            imgFloatData[index] = tmpStateSpace[index];
        }

        int sumDis = 0;
        msg        = "";
        msg += QString::fromLocal8Bit(
            "======================================\nNumber of pixels of each land use at %1 / %2\n")
                   .arg(k + 1)
                   .arg(this->numIternations);
        if (MUTILS::printCASimulationProcess) {
            cout << "\n======================================\n" << endl;
            cout << "Number of pixels of each land use at " << k + 1 << "/" << this->numIternations << endl;
            cout << "iteration: ";
        }

        int maxDiff = 0;
        for (int ii = 0; ii < nTypes; ii++) {
            if (MUTILS::printCASimulationProcess)
                cout << saveCount[ii] << "(" << landUseDemand[ii] - saveCount[ii] << ")"
                     << ", " << isPause;
            int tmp = abs(landUseDemand[ii] - saveCount[ii]);
            maxDiff = maxDiff > tmp ? maxDiff : tmp;
            msg += QString::fromLocal8Bit("%1, (%2), ").arg(saveCount[ii]).arg(landUseDemand[ii] - saveCount[ii]);
            sumDis += tmp;
        }
        // --->传回信息
        sendStringMSG(msg);
        sendLandCount(saveCount, k);
        //        emit signalSendImagData(this->imgFloatData, this->landUseImage->getBand(1));
        emit signalSendImagData(this->imgFloatData, this->landUseImage->getBand(1));
        m_endIterTimes++;
        if (sumDis == 0 || (sumDis < (pixelSum * 0.0001))) {
            break;
        }
        if (endDiffValue > 0 && maxDiff < endDiffValue) {
            break;
        }
        if (isToStop) {
            write2File(saveTifPath, cellMap, imgFloatData);

            // --->传回信息
            sendStringMSG("The simulation stopped early!!!");

            hasWrited = true;
            break;
        }
    }

    if (!hasWrited) {
        write2File(saveTifPath, cellMap, imgFloatData);
    }

    // 释放空间
    m_indexList.clear();
    delete[] tmpStateSpace;
    tmpStateSpace = NULL;
    freeMemories();
    emit isDone();
}

void CA_V2::initCells() {}

int CA_V2::char2Int(char c) { return (int)(c - '0'); }

char CA_V2::int2Char(int i) { return i + '0'; }

double *CA_V2::calNeighborsProportion(LandCell *cell) {
    double *portions = new double[this->nTypes];
    // 初始化
    for (int i = 0; i < this->nTypes; i++) {
        portions[i] = 0;
    }
    for (int i = 0; i < this->neiWindow; ++i) {
        int row = cell->getRow() + this->direction[i][0];
        int col = cell->getCol() + this->direction[i][1];
        // TODO 邻居越界跳过（采用）？循环？设置假邻居？
        if (row < 0 || col < 0 || row >= this->rows || col >= this->cols) continue;
        int index = row * this->cols + col;
        if (this->landUseImage->isValidLandPixels(index)) {
            portions[int(imgFloatData[index] - 1)] += 1;  // 上一轮的比例
        }
    }
    for (int i = 0; i < this->nTypes; i++) {
        portions[i] /= (double)neiWindow;
    }
    return portions;
}

int CA_V2::rouletteNewType(LandCell *cell, double landInertia) {
    int numOfClasses = nTypes;
    // 使用两期数据，在获取ANN概率时有偏移
    // 比如两期数据，4种土地类型，有16种变化，则土地1对应0-3，土地二对应4-7
    int     offset       = twoYears ? (cell->getLandType() - 1) * nTypes : 0;
    int     index        = cell->getIndex();
    int     curTypeIndex = cell->getLandType() - 1;
    double *combineProbs = new double[numOfClasses];
    double *roulette     = new double[numOfClasses + 1];
    // 计算邻域影响
    double *portion  = calNeighborsProportion(cell);
    double  sumProbs = 0;
    if (probImage->getValueByBandAndIndex(0 + offset, index) == -1) m_count++;
    for (int i = 0; i < numOfClasses; ++i) {
        float prob      = probImage->getValueByBandAndIndex(i + offset, index);
        prob            = prob < 0 ? 0.0001 : prob;  // 避免概率为负数
        combineProbs[i] = prob * (neiIntensity[i] * portion[i]) * costMatrix[curTypeIndex][i];
        combineProbs[i] *= curTypeIndex == i ? landInertia * 10 * numOfClasses : 1;
        sumProbs += combineProbs[i];
    }
    roulette[0] = 0;
    for (int i = 0; i < numOfClasses; ++i) {
        combineProbs[i] = sumProbs == 0 ? 0 : combineProbs[i] / sumProbs;
        roulette[i + 1] = roulette[i] + combineProbs[i];
    }

    /* roulette choice return a new type(start from 1)*/
    int    newType = cell->getLandType();
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
