#include "acca_v2.h"

ACCA_V2::ACCA_V2() {}

ACCA_V2::ACCA_V2(QObject *parent, QString filePath, bool needSleep) { m_needSleep = needSleep; }

double *ACCA_V2::calNeighborsProportion(LandCell *cell) {
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
            portions[char2Int(m_buffer[cell->getIndex()][i]) - 1] += 1;
        }
    }
    for (int i = 0; i < this->nTypes; i++) {
        portions[i] /= (double)neiWindow;
    }
    return portions;
}

void ACCA_V2::startSimulation() {
    isToStop = false;
    isPause  = false;
    loadFromConfigFile(configPath);
    qDebug() << QString::fromLocal8Bit("acca_v2异步模拟%1_%2").arg(acaRatio).arg(m_useFLUSFOfficialVersion);
    m_alpha = acaRatio;
    sendStringMSG(QString::fromLocal8Bit("acca异步模拟%1").arg(acaRatio));

    initAllVariables();
    LandCell *cell = new LandCell(-1, -1, -1);
    int       newTypeIndex, oldTypeIndex;
    //    bool                                   isConvert;
    twoYears          = this->usedYears == 2;
    bool    hasWrited = false;
    QString msg;
    float * tmpStateSpace = new float[rows * cols];
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

    initBufferAndMode();

    m_endIterTimes = 0;
    QList<double> listcellPercentInLMode;
    int           cellCountInLMode = 0;
    for (int k = 0; k < this->numIternations; ++k) {
        if (this->isPause) {
            --k;
            continue;
        }
        sendCurrentIter(k + 1);
        // ==== step1. 更新惯性系数 ====
        updateLandInertia(k);

        cellCountInLMode = 0;
        // step2. 执行转换
        foreach (int index, m_indexList) {
            // 此部分待修改
            if (isInRestricted(index)) {
                continue;
            }

            // 统计L模式的细胞个数
            cellCountInLMode += m_modes[index] == CVALUE::MODE::L ? 1 : 0;

            // 异步
            double randAlpha = MUTILS::getRandDoubleInRange(0, 1);
            if (randAlpha > m_alpha) {
                continue;
            }
            if (Global::changeAlphaSetMode) m_indexListOfModeUsed.append(index);  // 记录使用了模式的细胞下标

            // 初始化临时细胞
            cell->setLandType(imgFloatData[index]);
            cell->setIndex(index);
            cell->setRow(index / this->cols);
            cell->setCol(index % this->cols);

            switch (m_modes[index]) {
                case CVALUE::MODE::B:
                    break;
                case CVALUE::MODE::L:
                    updateBuffer(cell);
                    break;
                case CVALUE::MODE::U:
                    // 执行转换前保存上次迭代结果，所有变化以上一次的结果为基准
                    oldTypeIndex = cell->getLandType() - 1;

                    // ==== step2.1 获取一个cell候选类型 ====
                    newTypeIndex = rouletteNewType(cell, adjustment_effect[oldTypeIndex]) - 1;
                    // ==== step2.2 尝试从候选类型中选择一个土地类型进行转换 ====
                    int offset = twoYears ? (cell->getLandType() - 1) * nTypes : 0;
                    tryToAllocate(k, newTypeIndex, oldTypeIndex, cell,
                        probImage->getValueByBandAndIndex(newTypeIndex + offset, index));
                    tmpStateSpace[index] = cell->getLandType();
            }
        }
        listcellPercentInLMode << (double)cellCountInLMode / (double)m_indexList.size();
        if (Global::changeAlphaSetMode) {
            setRandModeWithModeUsed();      // 只改变上面通过alpha检验的像元的模式
            m_indexListOfModeUsed.clear();  // 清空
        } else {
            setRandMode();  // 改变所有元胞的模式
        }

        foreach (int index, m_indexList) { imgFloatData[index] = tmpStateSpace[index]; }

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
        if (m_needSleep) QThread::msleep((1 - m_alpha) * 150);  // 避免消息发送过快
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

    // 保存处于L模式的比例
    QFileInfo fi(MUTILS::string2Qstring(saveTifPath));
    QDir      parDir = fi.dir();
    //    qDebug() << listcellPercentInLMode;
    QSettings settings(parDir.absoluteFilePath("L_Mode_Percent.ini"), QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup("percent");
    for (int i = 0; i < listcellPercentInLMode.size(); i++) {
        settings.setValue(QString::number(i), listcellPercentInLMode.at(i));
    }
    settings.endGroup();
    listcellPercentInLMode.clear();

    // 释放空间
    m_indexList.clear();
    delete[] tmpStateSpace;
    tmpStateSpace = NULL;
    delete[] m_modes;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index = i * cols + j;
            delete[] m_buffer[index];
        }
    }
    delete[] m_buffer;
    freeMemories();
    emit isDone();
}

void ACCA_V2::setRandMode() {
    for (int index : m_indexList) {
        int rn = MUTILS::getRandIntInRange(0, 3);
        switch (rn) {
            case 0:
                m_modes[index] = CVALUE::MODE::B;
                break;
            case 1:
                m_modes[index] = CVALUE::MODE::L;
                break;
            default:
                m_modes[index] = CVALUE::MODE::U;
        }
    }
}

void ACCA_V2::setRandModeWithModeUsed() {
    for (int index : m_indexListOfModeUsed) {
        int rn = MUTILS::getRandIntInRange(0, 3);
        switch (rn) {
            case 0:
                m_modes[index] = CVALUE::MODE::B;
                break;
            case 1:
                m_modes[index] = CVALUE::MODE::L;
                break;
            default:
                m_modes[index] = CVALUE::MODE::U;
        }
    }
}

void ACCA_V2::initBufferAndMode() {
    m_modes  = new CVALUE::MODE[rows * cols];
    m_buffer = new char *[rows * cols];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int index       = i * cols + j;
            m_buffer[index] = new char[neiWindow];
            m_modes[index]  = CVALUE::MODE::B;
            for (int k = 0; k < this->neiWindow; ++k) {
                int row = i + this->direction[k][0];
                int col = j + this->direction[k][1];
                // TODO 邻居越界跳过（采用）？循环？设置假邻居？
                if (row < 0 || col < 0 || row >= this->rows || col >= this->cols) continue;
                int neiIndex       = row * this->cols + col;
                m_buffer[index][k] = int2Char(imgFloatData[neiIndex]);
            }
        }
    }
}

void ACCA_V2::updateBuffer(LandCell *cell) {
    for (int i = 0; i < this->neiWindow; ++i) {
        int row = cell->getRow() + this->direction[i][0];
        int col = cell->getCol() + this->direction[i][1];
        // TODO 邻居越界跳过（采用）？循环？设置假邻居？
        if (row < 0 || col < 0 || row >= this->rows || col >= this->cols) continue;
        int index = row * this->cols + col;
        if (this->landUseImage->isValidLandPixels(index)) {
            if (m_modes[index] == CVALUE::MODE::B) {
                m_buffer[cell->getIndex()][i] = int2Char(imgFloatData[index]);
            }
        }
    }
}

void ACCA_V2::setNeedSleep(bool needSleep) { m_needSleep = needSleep; }
