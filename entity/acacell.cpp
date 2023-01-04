#include "acacell.h"

ACACell::ACACell(int row, int col, int landType) : LandCell(row, col, landType) {
    // 初始时， 模式为B
    this->mode         = CVALUE::MODE::B;
    this->prevLandType = landType;
    m_isModeUsed       = false;
}

ACACell::~ACACell() {
    //    qDebug() << "ACACell";
    qDeleteAll(bufferCells);
    bufferCells.clear();
}

// 添加邻居和buffer
void ACACell::addOneNeighborCell(LandCell *cell) {
    this->neighborsMap.insert(cell->getIndex(), cell);
    BufferCell *bc      = new BufferCell();
    ACACell *   acaCell = dynamic_cast<ACACell *>(cell);
    bc->mode            = acaCell->getMode();
    bc->index           = acaCell->getIndex();
    bc->curr_landType   = acaCell->getLandType();
    this->bufferCells.insert(bc->index, bc);
}

void ACACell::updateBuffer() {
    ACACell *acaCell;
    if (this->mode == CVALUE::MODE::L) {
        for (LandCell *cell : this->neighborsMap) {
            acaCell = dynamic_cast<ACACell *>(cell);
            if (acaCell->getMode() == CVALUE::MODE::B) {
                this->bufferCells[acaCell->getIndex()]->setLandType(acaCell->getPrevLandType());
            }
        }
    }
}

void ACACell::copyCurr2Prev() { this->prevLandType = this->landType; }

void ACACell::setRandMode() {
    // 从0， 1， 2中随机选取一个数字
    int rn = MUTILS::getRandIntInRange(0, 3);
    switch (rn) {
        case 0:
            this->mode = CVALUE::MODE::B;
            break;
        case 1:
            this->mode = CVALUE::MODE::L;
            break;
        default:
            this->mode = CVALUE::MODE::U;
    }
}

void ACACell::setMode(CVALUE::MODE mode) { this->mode = mode; }

void ACACell::setPrevLandType(int tmp) { this->prevLandType = tmp; }

int ACACell::getPrevLandType() { return this->prevLandType; }

CVALUE::MODE ACACell::getMode() { return this->mode; }

//  计算邻域类型概率。这里使用buffer中的邻居状态
double *ACACell::calNeighborsProportion(int numOfClasses, int windowSize) {
    // 从buffer中读取
    double *portions = new double[numOfClasses];
    for (int i = 0; i < numOfClasses; i++) {
        portions[i] = 0;
    }

    for (BufferCell *bufferCell : this->bufferCells) {
        portions[bufferCell->getLandType() - 1] += 1;
    }

    for (int i = 0; i < numOfClasses; i++) {
        portions[i] /= (double)windowSize;
    }
    return portions;
}

bool ACACell::getIsModeUsed() const { return m_isModeUsed; }

void ACACell::setIsModeUsed(bool isModeUsed) { m_isModeUsed = isModeUsed; }
