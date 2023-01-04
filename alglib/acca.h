#ifndef ACCA_H
#define ACCA_H

#include "alglib/aca.h"
#include "alglib/ca.h"
#include "entity/acacell.h"
class ACCA : public ACA {
public:
    ACCA();
    ACCA(QObject* parent, QString filePath, double alpha = 0.5);

protected:
    void startSimulation() override;
    void initCells() override;
    void updateModeOfCells();
};

#endif  // ACCA_H
