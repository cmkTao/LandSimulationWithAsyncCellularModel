#ifndef DEMO_H
#define DEMO_H
#include <gdal_priv.h>
#include <thirdPart/json/json.h>

#include <QDebug>

#include "entity/cbatchcasimconfig.h"
namespace DEMO {
void demo();
void demoColor();
void demoCallPython();
void demoCallPythonEnv();
void demoReadDirs();
void demoJson();
}  // namespace DEMO
#endif  // DEMO_H
