#include "ca.h"
CA::CA() {
    configPath                = "";
    m_useFLUSFOfficialVersion = Global::useOfficialFlus;
}

CA::CA(QObject *parent, QString filePath) : QThread(parent) {
    this->threadCount         = 8;
    this->configPath          = filePath;
    imgFloatData              = NULL;
    m_useFLUSFOfficialVersion = Global::useOfficialFlus;
}

CA::~CA() { freeImgFloatData(); }

void CA::loadFromConfigFile(QString filePath) {
    int          nSize;
    int          i;
    Json::Reader reader;
    Json::Value  root, tempVal;
    bool         res;
    QByteArray   qByteArray = filePath.toUtf8();
    char *       path       = qByteArray.data();
    ifstream     in(path, ios::binary);

    if (!in.is_open()) {
        qDebug() << "Error opening file\n";
        return;
    }

    if (!reader.parse(in, root)) {
        qDebug() << "fail to parse json file" << endl;
        in.close();
        return;
    }

    //    cout <<"id: "<<root["id"].asString()<<endl;
    this->landUseTifPath = root["landUsePath"].asString();
    this->probsTifPath   = root["probsPath"].asString();
    this->saveTifPath    = root["saveSimPath"].asString();

    if (root.isMember("usedYears")) {
        this->usedYears = root["usedYears"].asInt();
    } else {
        this->usedYears = 1;
    }

    if (root.isMember("randNum")) {  // 随机数种子
        this->randomNum = root["randomNum"].asInt();
    } else {
        this->randomNum = -10;
    }

    if (root.isMember("restrictedPath")) {
        this->restrictedTifPath = root["restrictedPath"].asString();
        isRestrictExit          = true;
    } else {
        isRestrictExit = false;
    }

    this->numIternations = root["simConfig"]["maxIterNum"].asInt();
    this->neiSize        = root["simConfig"]["neighboorhoodOdd"].asInt();

    tempVal             = root["landUseDemand"];
    nSize               = tempVal.size();
    this->nTypes        = nSize;
    this->landUseDemand = new int[nSize];
    for (i = 0; i < nSize; i++) {
        this->landUseDemand[i] = tempVal[i].asInt();
    }

    tempVal            = root["weightOfNeighborhood"];
    nSize              = tempVal.size();
    this->neiIntensity = new double[nSize];
    for (i = 0; i < nSize; i++) {
        this->neiIntensity[i] = tempVal[i].asDouble();
    }

    tempVal          = root["costMatrix"];
    nSize            = tempVal.size();
    this->costMatrix = new double *[nSize];
    for (i = 0; i < nSize; i++) {
        this->costMatrix[i] = new double[nSize];
        for (int j = 0; j < nSize; j++) {
            this->costMatrix[i][j] = tempVal[i][j].asDouble();
        }
    }
    degree = root["degree"].asDouble();
    if (root.isMember("endDiffValue")) {
        endDiffValue = root["endDiffValue"].asInt();
    } else {
        endDiffValue = -1;  // 不起作用
    }

    // 同步率
    if (root.isMember("acaRatio")) {
        this->acaRatio = root["acaRatio"].asDouble();
    } else {
        this->acaRatio = 1.0;  // 默认同步
    }

    in.close();
    printDebug();
}

void CA::loadTifData() {
    this->landUseImage = new TifDataEntity(QString::fromStdString(this->landUseTifPath));
    this->NoDataValue  = this->landUseImage->getNoDataByBand();
    this->probImage    = new TifDataEntity(QString::fromStdString(this->probsTifPath));
    if (this->isRestrictExit) {
        this->restrictImage = new TifDataEntity(QString::fromStdString(this->restrictedTifPath));
    } else {
        this->restrictImage = NULL;
    }
    this->rows   = this->landUseImage->getRow();
    this->cols   = this->landUseImage->getCol();
    this->nTypes = this->landUseImage->getNTypes();
}

void CA::initAllVariables() {
    this->neiWindow = this->neiSize * this->neiSize - 1;
    this->direction = this->scanWindow(neiSize);

    loadTifData();
    imgFloatData = new float[this->landUseImage->getRow() * this->landUseImage->getCol()];
    initCells();

    mdNeiborhoodProbability = new double[nTypes];
    mdRoulette              = new double[nTypes + 1];
    probability             = new double[nTypes];
    initialProb             = new double[nTypes];
    adjustment              = new double[nTypes];
    adjustment_effect       = new double[nTypes];
    bestdis                 = new double[nTypes];
    saveCount               = new int[nTypes];
    opposite2reverse        = new double[nTypes];
    mIminDis2goal           = new double[nTypes];
    dynaDist                = new double[nTypes];
    initialDist             = new double[nTypes];
    pixelSum                = 0;
    for (int ii = 0; ii < this->nTypes; ii++) {
        mdNeiborhoodProbability[ii] = 0;
        mdRoulette[ii + 1]          = 0;
        probability[ii]             = 0;
        initialProb[ii]             = 0;
        bestdis[ii]                 = 0;
        // 自适应系数初始为1
        this->adjustment_effect[ii] = 1;
        // 统计初始的像素总数
        pixelSum += this->landUseImage->getLandCountByLandCode(ii + 1);
        // 该数组表示类型是否进制转移
        opposite2reverse[ii] = 0;
        saveCount[ii]        = this->landUseImage->getLandCountByLandCode(ii + 1);
    }
}

void CA::initCells() {
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
                LandCell *cell = new LandCell(i, j, landType);
                cell->setIndex(index);
                cell->setRestricted(this->isInRestricted(index));
                cell->setProbs(probs);
                this->cellMap.insert(index, cell);
            }
        }
    }

    // 初始化每个cell的邻居map
    initNeiOfCells();

    int     timeDiff    = time.elapsed();
    float   f           = timeDiff / 1000.0;
    QString tr_timeDiff = QString::fromLocal8Bit("初始化细胞用时：%1s").arg(f);
    qDebug() << tr_timeDiff;  // float->QString
}

void CA::initNeiOfCells() {
    //    QThreadPool       threadpoor1;
    //    int               len = this->cellMap.size();
    //    QList<QList<int>> ra  = MUTILS::splitN2Ranges(len, threadCount);
    //    threadpoor1.setMaxThreadCount(threadCount);
    //    for (int ii = 0; ii < threadCount; ii++) {
    //        QtConcurrent::run(&threadpoor1, [&, ra, ii]() {
    //            qDebug() << QThread::currentThreadId() << "==>" << ra[ii];
    //            int                                    row, col, index, i;
    //            QHash<int, LandCell *>::const_iterator cqmit = this->cellMap.cbegin() + ra[ii][0];
    //            for (int t = ra[ii][0]; t <= ra[ii][1]; ++cqmit, ++t) {
    //                LandCell *cell = cqmit.value();
    //                for (i = 0; i < this->neiWindow; ++i) {
    //                    row = cell->getRow() + this->direction[i][0];
    //                    col = cell->getCol() + this->direction[i][1];
    //                    if (row < 0 || col < 0 || row >= this->rows || col >= this->cols) continue;
    //                    index = row * this->cols + col;
    //                    if (this->landUseImage->isValidLandPixels(index)) {
    //                        cell->addOneNeighborCell(this->cellMap[index]);
    //                    }
    //                }
    //            }
    //        });
    //    }
    //    threadpoor1.waitForDone();

    // 初始化每个cell的邻居map
    int                                    row, col, index, i;
    QHash<int, LandCell *>::const_iterator cqmit = this->cellMap.cbegin();
    for (; cqmit != this->cellMap.cend(); ++cqmit) {
        LandCell *cell = cqmit.value();
        for (i = 0; i < this->neiWindow; ++i) {
            row = cell->getRow() + this->direction[i][0];
            col = cell->getCol() + this->direction[i][1];
            // TODO 邻居越界跳过（采用）？循环？设置假邻居？
            // 当前采用跳过边界和不合法邻居
            if (row < 0 || col < 0 || row >= this->rows || col >= this->cols) continue;
            index = row * this->cols + col;
            if (this->landUseImage->isValidLandPixels(index)) {
                cell->addOneNeighborCell(this->cellMap[index]);
            }
        }
    }
}

int CA::rouletteNewType(LandCell *cell, double landInertia) { return 0; }

double *CA::calNeighborsProportion(LandCell *cell) { return NULL; }

bool CA::isInRestricted(int index) {
    return isRestrictExit ? this->restrictImage->getFloatDataByBand()[index] == 0 : false;
}

void CA::startSimulation() {
    isToStop = false;
    isPause  = false;
    loadFromConfigFile(configPath);
    qDebug() << QString::fromLocal8Bit("ca异步模拟%1-%2").arg(acaRatio).arg(Global::useOfficialFlus);
    sendStringMSG(QString::fromLocal8Bit("ca异步模拟%1").arg(acaRatio));
    initAllVariables();
    QHash<int, LandCell *>::const_iterator cb;
    QHash<int, LandCell *>::const_iterator ce = this->cellMap.cend();
    LandCell *                             cell;
    int                                    newTypeIndex, oldTypeIndex;
    //    bool                                   isConvert;
    twoYears          = this->usedYears == 2;
    bool    hasWrited = false;
    QString msg;
    m_endIterTimes = 0;
    for (int k = 0; k < this->numIternations; ++k) {
        if (this->isPause) {
            --k;
            continue;
        }
        sendCurrentIter(k + 1);
        // ==== step1. 更新惯性系数 ====
        updateLandInertia(k);

        // step2. 执行转换
        for (cb = this->cellMap.cbegin(); cb != ce; ++cb) {
            cell = cb.value();

            // 异步
            double randAlpha = MUTILS::getRandDoubleInRange(0, 1);
            if (randAlpha > this->acaRatio) {
                continue;
            }

            // 跳过限制元素
            if (cell->isRestricted()) {
                continue;
            }

            oldTypeIndex = cell->getLandType() - 1;

            // ==== step2.1 获取一个cell候选类型 ====
            newTypeIndex = cell->allocateNewType(this->neiIntensity, costMatrix[oldTypeIndex],
                               adjustment_effect[oldTypeIndex], neiWindow, nTypes, twoYears)
                           - 1;
            // ==== step2.2 尝试从候选类型中选择一个土地类型进行转换 ====
            tryToAllocate(k, newTypeIndex, oldTypeIndex, cell);
        }

        // 执行转换前保存上次迭代结果，所有变化以上一次的结果为基准s
        for (cb = this->cellMap.cbegin(); cb != ce; ++cb) {
            cell = cb.value();
            cell->setLandTypeInLastTime(cell->getLandType());
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
    freeImgFloatData();
    emit isDone();
}

int **CA::scanWindow(int sizeWindows) {
    int _numWindows = sizeWindows * sizeWindows - 1;
    int i, k, f;
    direction = new int *[_numWindows];
    for (i = 0; i < _numWindows; i++) {
        direction[i] = new int[2];
    }
    // loop
    i = 0;
    for (k = -(sizeWindows - 1) / 2; k <= (sizeWindows - 1) / 2; k++) {
        for (f = -(sizeWindows - 1) / 2; f <= (sizeWindows - 1) / 2; f++) {
            if (!(k == 0 && f == 0)) {
                direction[i][0] = k;
                direction[i][1] = f;
                i++;
            }
        }
    }
    return direction;
}

void CA::updateLandInertia(int iter) {
    // 参照论文的实现
    //    for (int ii = 0; ii < nTypes; ii++) {
    //        // t - 1的差距
    //        mIminDis2goal[ii] = landUseDemand[ii] - saveCount[ii];
    //        // 初始年
    //        if (iter == 0) {
    //            // 初始差距
    //            initialDist[ii] = mIminDis2goal[ii];
    //            // 动态差距 = 初始差距 * 1.01 有细微差异就行，t-2的差距
    //            //                dynaDist[ii] = initialDist[ii] * 1.01;
    //            // t - 2 的差距
    //            dynaDist[ii] = initialDist[ii] * 1.01;
    //            // 该数组记录和目标的最小差异
    //            bestdis[ii] = initialDist[ii];
    //        }

    //        if (dynaDist[ii] > mIminDis2goal[ii] && dynaDist[ii] < 0) {  // 宏观需求少 差距拉大，减小惯性系数
    //            adjustment_effect[ii] = adjustment_effect[ii] * pow(dynaDist[ii] / mIminDis2goal[ii], 2);
    //        } else if (mIminDis2goal[ii] > dynaDist[ii] && dynaDist[ii] > 0) {  // 宏观需求多 差距拉大，增大惯性系数
    //            adjustment_effect[ii] = adjustment_effect[ii] * pow(mIminDis2goal[ii] / dynaDist[ii], 2);
    //        } else if (abs(dynaDist[ii]) < abs(mIminDis2goal[ii])) {  // 异号，差距拉大
    //            adjustment_effect[ii] = adjustment_effect[ii] * pow(abs(dynaDist[ii]) / abs(mIminDis2goal[ii]), 2);
    //        }
    //    }
    //    return;

    // 参照源码的实现
    for (int ii = 0; ii < nTypes; ii++) {
        // t - 1的差距
        mIminDis2goal[ii] = landUseDemand[ii] - saveCount[ii];
        // 初始年
        if (iter == 0) {
            // 初始差距
            initialDist[ii] = mIminDis2goal[ii];
            // 动态差距 = 初始差距 * 1.01 有细微差异就行，t-2的差距
            //                dynaDist[ii] = initialDist[ii] * 1.01;
            dynaDist[ii] = initialDist[ii] * 1.01;
            // 该数组记录和目标的最小差异
            bestdis[ii] = initialDist[ii];
        }
        // ================== 自适应系数 Intertia =======================================
        if (abs(bestdis[ii]) > abs(mIminDis2goal[ii])) {
            bestdis[ii] = mIminDis2goal[ii];
        } else {
            // t - 1比最小差异的绝对值大，且二者之差占初始差距的比例 > 5%， 则禁止转移
            //            if (initialDist[ii] == 0 || (abs(mIminDis2goal[ii]) - abs(bestdis[ii])) / abs(initialDist[ii])
            //            > 0.05) {
            //                opposite2reverse[ii] = 1;
            //            }
            if ((abs(mIminDis2goal[ii]) - abs(bestdis[ii])) / abs(initialDist[ii]) > 0.05) {
                opposite2reverse[ii] = 1;
            }
        }

        // mIminDis2goal 代表 t - 1
        // dynaDist 代表 t - 2
        //        if (dynaDist[ii] == 0) {
        //            dynaDist[ii] = 0.0001;
        //            continue;
        //        }
        adjustment[ii] = mIminDis2goal[ii] / dynaDist[ii];

        // t - 1和t - 2同号
        if (adjustment[ii] < 1 && adjustment[ii] > 0) {
            dynaDist[ii] = mIminDis2goal[ii];
            // 目标比当前多，因子变大，表示需要增加
            // degree加速因子
            if (initialDist[ii] > 0 && adjustment[ii] > (1 - degree)) {
                adjustment_effect[ii] = adjustment_effect[ii] * (adjustment[ii] + degree);
            }
            // 目标比当前少，因子变小，表示需要减少
            if (initialDist[ii] < 0 && adjustment[ii] > (1 - degree)) {
                adjustment_effect[ii] = adjustment_effect[ii] * (1 / (adjustment[ii] + degree));
            }
        }

        // 当前比目标小，则乘以 调整因子^3
        if ((initialDist[ii] > 0 && adjustment[ii] > 1)) {
            //                adjustment_effect[ii] = adjustment_effect[ii] * adjustment[ii] * adjustment[ii];
            adjustment_effect[ii] = adjustment_effect[ii] * adjustment[ii] * adjustment[ii];
        }
        // 当前比目标大，则乘以 1 / 调整因子^3
        if ((initialDist[ii] < 0 && adjustment[ii] > 1)) {
            //                adjustment_effect[ii] = adjustment_effect[ii] * (1.0 / adjustment[ii]) * (1.0 /
            //                adjustment[ii]);
            adjustment_effect[ii] = adjustment_effect[ii] * (1.0 / adjustment[ii]) * (1.0 / adjustment[ii]);
        }
    }
}

// 尝试将当前像元转为目标土地类型
void CA::tryToAllocate(int k, int newTypeIndex, int oldTypeIndex, LandCell *cell, double newTypeProb) {
    bool isConvert;
    // ==== 判断是否向候选类型转换 ====
    if ((newTypeIndex != oldTypeIndex) && (costMatrix[oldTypeIndex][newTypeIndex] != 0)) {
        isConvert = true;
    } else {
        isConvert = false;
    }

    //    double _disChangeFrom;
    //    _disChangeFrom = abs(mIminDis2goal[oldTypeIndex]);

    //    double _disChangeTo;
    //    _disChangeTo = abs(mIminDis2goal[newTypeIndex]);

    //    if (_disChangeTo == 0) {
    //        adjustment_effect[newTypeIndex] = 1;
    //        isConvert                       = false;
    //    }

    //    if (_disChangeFrom == 0) {
    //        adjustment_effect[oldTypeIndex] = 1;
    //        isConvert                       = false;
    //    }

    // 保留
    double _disChangeFrom;
    _disChangeFrom = mIminDis2goal[oldTypeIndex];

    double _disChangeTo;
    _disChangeTo = mIminDis2goal[newTypeIndex];

    if (initialDist[newTypeIndex] >= 0 && _disChangeTo == 0) {
        adjustment_effect[newTypeIndex] = 1;
        isConvert                       = false;
    }

    if (initialDist[oldTypeIndex] <= 0 && _disChangeFrom == 0) {
        adjustment_effect[oldTypeIndex] = 1;
        isConvert                       = false;
    }

    if (initialDist[oldTypeIndex] >= 0 && opposite2reverse[oldTypeIndex] == 1) {
        isConvert = false;
    }
    if (initialDist[newTypeIndex] <= 0 && opposite2reverse[newTypeIndex] == 1) {
        isConvert = false;
    }
    // =====
    //    if (cell->getProbs() == NULL && newTypeProb == -1) qDebug() << QString::fromLocal8Bit("概率文件有问题!!");
    newTypeProb = cell->getProbs() != NULL ? cell->getANNProbsByType(newTypeIndex + 1, nTypes, twoYears) : newTypeProb;
    if (Global::useProbCheck) {  // 进行概率检查
        if (isConvert == true) {
            double rdmData3 = MUTILS::getRandDoubleInRange(0, 1);
            if ((rdmData3 + (1.0 / nTypes)) / ((k + 1)) < newTypeProb) {
                isConvert = true;
            } else {
                isConvert = false;
            }
        }
    }

    if (isConvert == true) {
        cell->setLandType(newTypeIndex + 1);
        saveCount[newTypeIndex] += 1;
        saveCount[oldTypeIndex] -= 1;
        mIminDis2goal[newTypeIndex] = landUseDemand[newTypeIndex] - saveCount[newTypeIndex];
        mIminDis2goal[oldTypeIndex] = landUseDemand[oldTypeIndex] - saveCount[oldTypeIndex];
    }

    // 注释以下两句将 会和原版FLUS运行一直
    if (!Global::useOfficialFlus) {
        opposite2reverse[oldTypeIndex] = 0;
        opposite2reverse[newTypeIndex] = 0;
    }
}

void CA::sendStringMSG(const QString msg) { emit signalSendMessage(msg); }

void CA::sendLandCount(int *land_count, int key) { emit signalSendLandCounts(land_count, key); }

void CA::sendImageData() {
    if (!MUTILS::showCASimulationProcessImages) return;
    QHash<int, LandCell *>::const_iterator cqmit = this->cellMap.cbegin();
    int                                    index;
    for (; cqmit != this->cellMap.cend(); ++cqmit) {
        index                     = cqmit.value()->getIndex();
        this->imgFloatData[index] = cqmit.value()->getLandType();
    }
    // 为了使用utils.h的getColorMap()，所以传回两个参数
    emit signalSendImagData(this->imgFloatData, this->landUseImage->getBand(1));
}

void CA::sendCurrentIter(int k) { emit signalSendProcess(k); }

void CA::freeMemories() {
    if (!MUTILS::showCASimulationProcessImages) {
        freeImgFloatData();
    }

    delete landUseImage;
    landUseImage = NULL;

    delete probImage;
    probImage = NULL;

    if (this->restrictImage != NULL) {
        delete restrictImage;
        restrictImage = NULL;
    }

    for (int i = 0; i < neiWindow; i++) {
        delete[] direction[i];
    }
    delete[] direction;
    direction = NULL;

    delete[] landUseDemand;
    landUseDemand = NULL;

    delete[] neiIntensity;
    neiIntensity = NULL;

    for (int i = 0; i < nTypes; i++) {
        delete[] costMatrix[i];
    }
    delete[] costMatrix;
    costMatrix = NULL;

    delete[] mdNeiborhoodProbability;
    mdNeiborhoodProbability = NULL;

    delete[] mdRoulette;
    mdRoulette = NULL;

    delete[] probability;
    probability = NULL;

    delete[] initialProb;
    initialProb = NULL;

    delete[] adjustment_effect;
    adjustment_effect = NULL;

    delete[] adjustment;
    adjustment = NULL;

    delete[] mIminDis2goal;
    mIminDis2goal = NULL;

    delete[] initialDist;
    initialDist = NULL;

    delete[] dynaDist;
    dynaDist = NULL;

    delete[] bestdis;
    bestdis = NULL;

    delete[] opposite2reverse;
    opposite2reverse = NULL;

    delete[] saveCount;
    saveCount = NULL;

    //    landUseTifPath.clear();
    //    probsTifPath.clear();
    //    restrictedTifPath.clear();
    //    saveTifPath.clear();
}

void CA::freeCellSpace() {
    qDeleteAll(cellMap);
    cellMap.clear();
}

int CA::endIterTimes() const { return m_endIterTimes; }

// ================== Setter And Getter ====================
void CA::setLandUsePath(string tmp) { this->landUseTifPath = tmp; }

void CA::setProbsPath(string tmp) { this->probsTifPath = tmp; }

void CA::setSaveTifPath(string tmp) { this->saveTifPath = tmp; }

void CA::setRestrictedTifPath(string tmp) {
    this->restrictedTifPath = tmp;
    this->isRestrictExit    = true;
}

void CA::setUsedYears(int tmp) { this->usedYears = tmp; }

void CA::setRandomNum(int tmp) { this->randomNum = tmp; }

void CA::setNumIternations(int tmp) { this->numIternations = tmp; }

void CA::setNeiSize(int tmp) { this->neiSize = tmp; }

void CA::setLandUseDemand(int *tmp) { this->landUseDemand = tmp; }

void CA::setNeiIntensity(double *tmp) { this->neiIntensity = tmp; }

void CA::setCostMatrix(double **tmp) { this->costMatrix = tmp; }

void CA::setDegree(int tmp) { this->degree = degree; }

void CA::setConfigPath(QString tmp) { this->configPath = tmp; }

void CA::setStopFlag(bool tmp) { this->isToStop = true; }

void CA::setPauseFlag(bool tmp) {
    if (tmp) {
        sendStringMSG("\n++++++++++++++++++++The simulation is pausing...\n+++++++++++++++++++++");
    }
    isPause = tmp;
}

void CA::freeImgFloatData() {
    if (imgFloatData != NULL) {
        delete[] imgFloatData;
        imgFloatData = NULL;
    }
}

void CA::run_test() {
    qDebug() << 123;
    //    loadFromConfigFile(configPath);
    //    initAllVariables();
    //    //    qDebug() << 456;
    //    startSimulation();
    //    VLDReportLeaks();
    startSimulation();
}

void CA::printDebug() {
    qDebug() << MUTILS::string2Qstring(this->landUseTifPath);
    qDebug() << MUTILS::string2Qstring(this->probsTifPath);
    qDebug() << MUTILS::string2Qstring(this->saveTifPath);
    qDebug() << QString("usedYears=%1").arg(usedYears);
    qDebug() << QString("acaRatio=%1").arg(acaRatio);
}

void CA::run() { startSimulation(); }

void CA::write2File(string filePath, QHash<int, LandCell *> cellMap, float *landImagData) {
    // register
    GDALAllRegister();
    // OGRRegisterAll();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");

    TiffDataRead *pread = new TiffDataRead;
    pread->loadFrom(landUseTifPath.c_str());
    double noDataValue = 255;
    pread->convert2uchar();
    int index;
    if (landImagData == NULL) {
        QHash<int, LandCell *>::const_iterator cb;
        QHash<int, LandCell *>::const_iterator ce = this->cellMap.cend();
        for (cb = this->cellMap.cbegin(); cb != ce; ++cb) {
            index                   = cb.value()->getIndex();
            pread->imgData()[index] = cb.value()->getLandType();
        }
    } else {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                index = r * cols + c;
                if (landUseImage->isValidLandPixels(index)) pread->imgData()[index] = (int)imgFloatData[index];
            }
        }
    }
    // 写入文件
    size_t        i, j, k;
    TiffDataWrite pwrite;
    bool          isExist = false;
    bool          brlt;
    fstream       _file;
    _file.open(filePath, ios::in);
    if (_file) {
        isExist = true;
    }
    _file.close();
    QString qfilePath = QString::fromStdString(filePath);
    QString msg;
    if (isExist) {
        // --> 传回信息
        sendStringMSG(QString::fromLocal8Bit("\nWarnings: %1 will be deleted!!!").arg(qfilePath));
        cout << "\nWarnings: " << filePath << " will be deleted!!!" << endl;

        // 目前目标tif必须不存在才能创建
        if (QFile::remove(qfilePath)) {
            msg = QString::fromLocal8Bit("%1 删除成功！").arg(qfilePath);
            cout << filePath << " 删除成功！" << endl;
        } else {
            msg = QString::fromLocal8Bit("%1 删除失败！").arg(qfilePath);
            cout << filePath << " 删除失败！" << endl;
        }
        // --> 传回信息
        sendStringMSG(msg);
    }
    brlt = pwrite.init(filePath.c_str(), pread->rows(), pread->cols(), 1, pread->geotransform(), pread->projectionRef(),
        GDT_Byte, noDataValue);
    if (!brlt) {
        cout << "写入失败" << endl;
        sendStringMSG("写入失败");
        return;
    }
    unsigned char _val = 0;
    if (pread->imgData() != NULL) {
        for (i = 0; i < pwrite.rows(); i++) {
            for (j = 0; j < pwrite.cols(); j++) {
                for (k = 0; k < pwrite.bandnum(); k++) {
                    _val = pread->imgData()[k * pwrite.rows() * pwrite.cols() + i * pwrite.cols() + j];
                    pwrite.write(i, j, k, &_val);
                }
            }
        }
        cout << endl << filePath << "--> write success!" << endl;
        sendStringMSG(QString::fromLocal8Bit("%1 --> write success!").arg(qfilePath));
    }
    pwrite.close();
    delete pread;
    pread = NULL;
}
// ------------------ Setter And Getter --------------------
