#include "acca.h"

ACCA::ACCA() {}

ACCA::ACCA(QObject *parent, QString filePath, double alpha) : ACA(parent, filePath, alpha) {}

void ACCA::startSimulation() {}

void ACCA::initCells() {}

void ACCA::updateModeOfCells() {}
