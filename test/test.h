
/**
 * @projectName   qtmflus
 * @brief         摘要
 * @author        cmk
 * @date          2020-11-10
 */

#ifndef TEST_H
#define TEST_H

#include <QList>
#include <fstream>
#include <iostream>

//#include "alglib/annthread.h"
#include "alglib/ca.h"
#include "utils/mutils.h"
#include "utils/tifTools.h"
namespace TEST {
void testTifWrite();
void testSyncSim();

void testType();

void testShark();

void testTorch();

void testClean();

void testAnn();
}  // namespace TEST
#endif  // TEST_H
