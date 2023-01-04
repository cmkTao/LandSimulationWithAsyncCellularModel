#include <QApplication>
#include <QLabel>
#include <QRandomGenerator>
#include <QStyleFactory>

#include "dialog.h"
#include "entity/tifdataentity.h"
#include "mainwindow.h"
#include "utils/config.h"

void getPath(QString);
#ifdef QT_NO_DEBUG
#else
#include "test/demo.h"
//#include "test/test.h"

#endif

#ifdef _DEBUG
#include "alglib/ca.h"
#include "alglib/validationthread.h"
//#include "vld.h"
#endif

#ifdef QT_NO_DEBUG
#else
void test() {
    DEMO::demo();
    //    VLDGlobalEnable();
    //    CA* vt = new CA();
    //    vt->setConfigPath(
    //        "D:\\litao\\learnMaterial\\ug3\\Land_simulation\\experiment\\datas\\resample_hgs\\10\\exp_config\\one_"
    //        "year\\ann_ca\\ca_"
    //        "config.json");
    //    vt->startSimulation();
    //    delete vt;
    //    VLDReportLeaks();
    //    ValidationThread* vt = new ValidationThread(0);
    //    vt->setEvalConfigPath(
    //        "D:\\litao\\learnMaterial\\ug3\\Land_simulation\\experiment\\datas\\resample_hgs\\10\\exp_config\\one_"
    //        "year\\ann_ca\\eval_"
    //        "config.json");
    //    vt->test();
    //    VLDReportLeaks();
    //    VLDGlobalDisable();
    //    DEMO::demoReadDirs();
    //    DEMO::demoJson();
    //    DEMO::demoCallPython();
    //    DEMO::demoCallPythonEnv();
    //    TEST::testTifWrite();
    //    TEST::testSyncSim();
    //    TifDataEntity tif();
    //    TEST::testTorch();
    //    TEST::testClean();
    //    TEST::testAnn();
}
#endif

int main(int argc, char* argv[]) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
#endif
    QApplication a(argc, argv);
    MainWindow   w;
    QDir::setCurrent(a.applicationDirPath());
//        test();
    w.show();
    return a.exec();
}
