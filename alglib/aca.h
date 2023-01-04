#ifndef ACA_H
#define ACA_H
#include <QtConcurrent>
#include <functional>

#include "alglib/ca.h"
#include "entity/acacell.h"
using namespace QtConcurrent;

class ACA : public CA {
public:
    ACA();
    ACA(QObject *parent, QString filePath, double alpha = 0.5);
    void  setAlpha(float tmp);
    float getAlpha();

protected:
    void startSimulation() override;
    void initCells() override;
    void freeCellSpace() override;
    void updateModeOfCells();

private:
    float alpha;
};

#endif  // ACA_H
