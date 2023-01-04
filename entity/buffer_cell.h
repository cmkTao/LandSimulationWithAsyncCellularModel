/**
 * @projectName   qtmflus
 * @brief         摘要
 * buffer中的内容
 * @author        cmk
 * @date          2020-11-27
 */

#ifndef BUFFER_CELL_H
#define BUFFER_CELL_H
#include "utils/constValue.h"
struct BufferCell {
    CVALUE::MODE mode;
    int          index;
    int          curr_landType;
    int          prev_landType;
    int          t;

    int  getLandType() { return curr_landType; }
    void setLandType(int tmp) { curr_landType = tmp; }

    int getCurrLandType() { return curr_landType; }

    void setCurrLandType(int tmp) { curr_landType = tmp; }

    int getPrevLandType() { return getPrevLandType(); }

    void setPrevLandType(int tmp) { prev_landType = tmp; }

    void setTime(int tmp) { t = tmp; }
    int  getTime(int tmp) { return t; }
};
#endif  // BUFFER_CELL_H
