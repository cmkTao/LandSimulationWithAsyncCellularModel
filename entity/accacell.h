#ifndef ACCACELL_H
#define ACCACELL_H

#include "entity/landcell.h"
class ACCACell : public LandCell {
public:
    ACCACell(int row, int col, int landType);

private:
    // ================= Functions =============

    // ================= Attribute =============
    int curr_state;
    int prev_state;
    int t;
};

#endif  // ACCACELL_H
