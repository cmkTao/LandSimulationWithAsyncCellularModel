#ifndef CLEANDATATHREAD_H
#define CLEANDATATHREAD_H
#include "alglib/cqthread.h"
#include "entity/tifdataentity.h"
#include "utils/mutils.h"
#include "utils/tifTools.h"
class CleanDataThread : public CQThread {
    Q_OBJECT
public:
    CleanDataThread(QObject *parent, QString inputDir, QString outputDir, QString inputLandPath, int neiWidth);

protected:
    // QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();

private:
    QString inputDir;
    QString outputDir;
    QString inputLandPath;
    int     neiWidth;
};

#endif  // CLEANDATATHREAD_H
