/**
 * @projectName   qtmflus
 * @brief         摘要
 * ACA异步Cell
 * @author        cmk
 * @date          2020-11-27
 */

#ifndef ACACELL_H
#define ACACELL_H
#include <QDebug>

#include "entity/buffer_cell.h"
#include "entity/landcell.h"
#include "utils/constValue.h"
#include "utils/mutils.h"
class ACACell : public LandCell {
public:
    ACACell(int row, int col, int landType);
    ~ACACell();

    void addOneNeighborCell(LandCell *cell) override;

    // L模式更新buffer
    void updateBuffer();

    // 保存当前状态到prevLandType中
    void copyCurr2Prev();

    // =============== setter and getter ===========
    void         setRandMode();
    void         setMode(CVALUE::MODE mode);
    void         setPrevLandType(int tmp);
    int          getPrevLandType();
    CVALUE::MODE getMode();

    bool getIsModeUsed() const;
    void setIsModeUsed(bool isModeUsed);

protected:
    // 从写函数，从buffer读取邻居比例
    double *                calNeighborsProportion(int numOfClasses, int windowSize = 9) override;
    CVALUE::MODE            mode;
    int                     prevLandType;
    QMap<int, BufferCell *> bufferCells;
    bool                    m_isModeUsed;  // 模式是否被用过了
};

#endif  // ACACELL_H
