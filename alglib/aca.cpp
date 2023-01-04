#include "aca.h"

ACA::ACA() { this->alpha = 0.5; }

ACA::ACA(QObject *parent, QString filePath, double alpha) : CA(parent, filePath) { this->alpha = alpha; }

void ACA::setAlpha(float tmp) { this->alpha = tmp; }

float ACA::getAlpha() { return this->alpha; }

void ACA::startSimulation() {
    this->isPause  = false;
    this->isToStop = false;
    loadFromConfigFile(configPath);
    this->alpha = this->acaRatio;
    qDebug() << QString::fromLocal8Bit("ACA异步模拟%1_%2").arg(alpha).arg(Global::useOfficialFlus);
    sendStringMSG(QString::fromLocal8Bit("ACA异步模拟%1").arg(alpha));
    initAllVariables();
    QHash<int, LandCell *>::const_iterator cb;
    QHash<int, LandCell *>::const_iterator ce = this->cellMap.cend();
    ACACell *                              acaCell;
    int                                    newTypeIndex, oldTypeIndex;
    //    bool                                   isConvert;
    twoYears          = this->usedYears == 2;
    bool    hasWrited = false;
    double  randAlpha;
    QString msg;
    m_endIterTimes = 0;
    for (int k = 0; k < this->numIternations; ++k) {
        // ======================== 模拟主体 =============================
        if (this->isPause) {
            --k;
            continue;
        }
        sendCurrentIter(k + 1);
        // ==== step1. 更新惯性系数 ====
        updateLandInertia(k);

        // ==== step2. 执行转换 ====

        for (cb = this->cellMap.cbegin(); cb != ce; ++cb) {
            acaCell = dynamic_cast<ACACell *>(cb.value());
            // 跳过限制元素
            if (acaCell->isRestricted()) continue;

            randAlpha = MUTILS::getRandDoubleInRange(0, 1);

            // step2.1 alpha
            if (randAlpha > this->alpha) {
                acaCell->setIsModeUsed(false);  // 模式未被使用，则不修改模式
                continue;
            }
            acaCell->setIsModeUsed(true);  // 模式被使用，要修改模式
            // ==== step2.2 mode ====
            switch (acaCell->getMode()) {
                case CVALUE::MODE::B:
                    break;
                case CVALUE::MODE::L:
                    acaCell->updateBuffer();
                    break;
                case CVALUE::MODE::U:
                    oldTypeIndex = acaCell->getLandType() - 1;

                    // ==== step2.1 获取一个cell候选类型 ====
                    newTypeIndex = acaCell->allocateNewType(this->neiIntensity, costMatrix[oldTypeIndex],
                                       adjustment_effect[oldTypeIndex], neiWindow, nTypes, twoYears)
                                   - 1;
                    // ==== step2.2 尝试从候选类型中选择一个土地类型进行转换 ====
                    tryToAllocate(k, newTypeIndex, oldTypeIndex, acaCell);
                    break;
            }
        }

        // step3 update mode randomly
        updateModeOfCells();

        // 将上一轮的状态记录到pre
        for (cb = this->cellMap.cbegin(); cb != ce; ++cb) {
            acaCell = dynamic_cast<ACACell *>(cb.value());
            acaCell->copyCurr2Prev();
        }

        // ========================= 输出相关信息 ==================================
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
            sumDis = sumDis + abs(mIminDis2goal[ii]);
        }
        // --->传回信息
        sendStringMSG(msg);
        sendLandCount(saveCount, k);
        sendImageData();
        m_endIterTimes++;

        if (sumDis == 0 || (sumDis < (pixelSum * 0.0001))) {
            break;
        }

        if (endDiffValue > 0 && maxDiff < endDiffValue) {
            break;
        }

        if (isToStop) {
            write2File(saveTifPath, cellMap);

            // --->传回信息
            sendStringMSG("The simulation stopped early!!!");

            hasWrited = true;
            break;
        }
    }

    if (!hasWrited) {
        write2File(saveTifPath, cellMap);
    }

    // 释放空间
    freeCellSpace();
    freeMemories();
    emit isDone();
}

void ACA::initCells() {
    qDebug() << QThread::currentThreadId();
    int     i = 0, j = 0, k, index, landType;
    double *probs;
    int     probBands = this->probImage->getBandCounts();
    QTime   time;
    time.start();
    //    QList<LandCell *> cellList;
    for (; i < this->rows; ++i) {
        for (j = 0; j < this->cols; ++j) {
            // 计算一维中的相对位置
            index = i * this->cols + j;
            // 保存临时数据
            this->imgFloatData[index] = this->landUseImage->getFloatDataByBand()[index];
            // 排除无效值元素
            if (this->landUseImage->isValidLandPixels(index)) {
                probs = new double[probBands];
                for (k = 0; k < probBands; ++k) {
                    probs[k] = this->probImage->getValueByBandAndIndex(k, index);
                }
                landType       = this->landUseImage->getFloatDataByBand()[index];
                LandCell *cell = new ACACell(i, j, landType);
                cell->setIndex(index);
                cell->setRestricted(this->isInRestricted(index));
                cell->setProbs(probs);
                this->cellMap.insert(index, cell);
            }
        }
    }

    // 初始化邻居
    initNeiOfCells();

    int     timeDiff    = time.elapsed();
    float   f           = timeDiff / 1000.0;
    QString tr_timeDiff = QString::fromLocal8Bit("初始化细胞用时：%1s").arg(f);
    qDebug() << tr_timeDiff;  // float->QString
}

void ACA::freeCellSpace() {
    ACACell *                              acaCell;
    QHash<int, LandCell *>::const_iterator cb;
    QHash<int, LandCell *>::const_iterator ce = this->cellMap.cend();
    for (cb = this->cellMap.cbegin(); cb != ce; ++cb) {
        acaCell = dynamic_cast<ACACell *>(cb.value());
        delete acaCell;
        acaCell = NULL;
    }
}

void ACA::updateModeOfCells() {
    QHash<int, LandCell *>::const_iterator cb = this->cellMap.cbegin();
    //    qDebug() << dynamic_cast<ACACell *>(cb.value())->getMode() << "=======-------";
    QHash<int, LandCell *>::const_iterator ce = this->cellMap.cend();
    for (; cb != ce; ++cb) {
        ACACell *acaCell = dynamic_cast<ACACell *>(cb.value());
        if (acaCell->getIsModeUsed()) {
            acaCell->setRandMode();         // 模式被用过才修改
            acaCell->setIsModeUsed(false);  // 新模式未被使用过
        }
    }
}
