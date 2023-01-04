#ifndef VALIDATIONTHREAD_H
#define VALIDATIONTHREAD_H
#include <gdal.h>
#include <gdal_priv.h>

#include <QMetaType>
#include <QThread>
#include <fstream>

#include "entity/tifdataentity.h"
#include "thirdPart/json/json.h"
#include "utils/mutils.h"
using namespace std;
class ValidationThread : public QThread {
    Q_OBJECT
public:
    ValidationThread(QObject *parent);

    void setEvalConfigPath(const QString &evalConfigPath);
    void test();

signals:
    void isDone(QList<QList<double>>);  //处理完成信号
    //    void signalSendMessage(QString);
    //    void signalSendProcess(int);
    //    void signalSendLandCounts(int *, int);
    //    void signalSendImagData(float *, GDALRasterBand *);

protected:
    // QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();

private:
    bool   isFileExists(QString path);
    void   loadFromConfig();
    void   startValidation();
    double calFom(TifDataEntity *startTif, TifDataEntity *endTif, TifDataEntity *simTif);

    /* 属性 */

    QString        m_evalConfigPath;
    QList<QString> m_simPathList;
    QString        m_startTifPath;  // 模拟起点
    QString        m_endTifPath;    // 模拟终点
    TifDataEntity *m_startTif;
    TifDataEntity *m_endTif;
};

#endif  // VALIDATIONTHREAD_H
