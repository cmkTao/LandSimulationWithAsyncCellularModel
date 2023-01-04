#ifndef CLEANLANDDATATHREAD_H
#define CLEANLANDDATATHREAD_H
#include "alglib/cqthread.h"
#include "entity/tifdataentity.h"
#include "utils/mutils.h"
#include "utils/tifTools.h"
class CleanLandDataThread : public CQThread {
    Q_OBJECT
public:
    CleanLandDataThread(QObject *parent, QString startTifPath, QString targetTifPath, QString savePath);

protected:
    // QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();

private:
    QString startTifPath;
    QString targetTifPath;
    QString savePath;
};

#endif  // CLEANLANDDATATHREAD_H
