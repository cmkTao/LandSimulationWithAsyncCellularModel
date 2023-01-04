#ifndef COMMONRUNNABLETASK_H
#define COMMONRUNNABLETASK_H

#include <alglib/aca.h>
#include <alglib/acca_v2.h>
#include <alglib/ca.h>
#include <alglib/ca_v2.h>
#include <entity/cbatchcasimconfig.h>

#include <QObject>
#include <QRunnable>

class CommonRunnableTask : public QObject, public QRunnable {
    Q_OBJECT

signals:
    void finished(int row);
    /**
     * @brief signalSendProcess
     * arg1: 配置所在表格行
     * arg2: 当前配置的第几次重复运行
     */
    void signalSendProcess(int row, int epoch);  // 传递进度

    void signalEpochFinished(int row, int epoch, int endIterTimes);  // 一轮运行完的信号
    void signalStartRun(int row);

public:
    CommonRunnableTask(char funType, CBatchCaSimConfig *cb, int rowInTable = 0);

protected:
    void run() override;

    // QRunnable interface
public:
    char               m_funType;
    CBatchCaSimConfig *m_cb;
    int                m_rowInTable;  // 在表格中的行数

    static char Sim;  // 用于模拟
    static char Val;  // 用于验证
};

#endif  // COMMONRUNNABLETASK_H
