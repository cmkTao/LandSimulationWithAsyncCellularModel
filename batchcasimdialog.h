#ifndef BATCHCASIMDIALOG_H
#define BATCHCASIMDIALOG_H

#include <windows.h>

#include <QDialog>
#include <QListView>
#include <QScrollBar>
#include <QTableWidgetItem>
#include <QThreadPool>
#include <QTreeView>
#include <iostream>

#include "alglib/aca.h"
#include "alglib/ca.h"
#include "alglib/commonrunnabletask.h"
#include "alglib/validationthread.h"
#include "entity/cbatchcasimconfig.h"
#include "utils/constValue.h"
#include "utils/mutils.h"
using namespace std;

namespace Ui {

class BatchCASimDialog;
}  // namespace Ui

class BatchCASimDialog : public QDialog {
    Q_OBJECT

public:
    explicit BatchCASimDialog(QWidget *parent = nullptr);
    ~BatchCASimDialog();
    void           loadConfigDirsToTW(QList<QString> dirPaths);
    QList<QString> loadSubDirs(QString dirPath);
    void           addOneConfigToTW(CBatchCaSimConfig *cb);
    void           createThread(CBatchCaSimConfig *cb);
    void           evalSimResult(CBatchCaSimConfig *cb, bool useCPlus = false);
    void           reset();
    QStringList    GetMultiDirectory();
    void           startSimulationByThreadPool();
private slots:
    void on_pb_targetPath_clicked();

    void on_pb_logPath_clicked();

    void on_pb_runDir_clicked();

    void on_btn_start_clicked();
    void setMSGFromThread2UI(QString);
    void slotProcessFinshed();
    void slotEvalProcessFinshed();
    void slotEvalProcessFinshed(QList<QList<double>>);
    void setProcess2Bar(int);
    void slotSetLandCounts(int *, int);
    void setRes2Te();

    void saveSummaryLogToIniFile(CBatchCaSimConfig *cb, QString mode = "sim");
    void initCBBySumLogFile(CBatchCaSimConfig *cb);

    void on_pushButton_clicked();

    void on_btn_stop_clicked();

    void on_pb_starPath_clicked();

    void on_pb_probFile_clicked();

    void on_btn_start_clicked(bool checked);

    /* QRunnable槽函数 */
    void slotRunnableFinshed(int row);
    void slotRunnableOneEpochFinshed(int row, int epoch, int endIterTimes);  // 一轮已经运行完毕
    void slotTaskStart(int row);                                             // 任务开始运行

private:
    Ui::BatchCASimDialog *ui;

    QTableWidgetItem *genTWI(QString content);
    QTableWidgetItem *genTWI(int content);
    QTableWidgetItem *genTWI(float content);
    QTableWidgetItem *genTWI(double content);

    void startASimulation();     // 开启一个模拟
    void startEvalSimulation();  // 开启一个模拟
    void saveLogs();             // 保存日志
    QDir getOrCreateLogsDir();   // 创建日志保存目录

    void getEpochFromlogIniFile(QString logPath);  // 从日志文件中读取上次运行的epoch数

    void initTable();
    void ui2ParamJson();

    /*                属性             */
    QString                            m_endYearTifPath;     // 模拟目标年份的真实文件路径
    QString                            m_startYearTifPath;   // 模拟起始年份的真实文件路径
    QString                            m_probTifPath;        // 适应性概率文件位置
    QString                            m_summaryLogPath;     // 本次批量运行总日志文件保存位置
    QString                            m_batchSimDir;        // 需要批量运行的配置所在的目录
    QString                            m_batchSimDirName;    // 当前目录名称
    int                                m_epochOfEachConfig;  //  每一个配置运行的轮数
    QMap<QString, CBatchCaSimConfig *> m_configMap;
    QMap<QString, int>                 m_rowNumPathMap;
    bool                               m_isSimulationMode;  // 模拟(true)/验证(false)
    CVALUE::BatchRunStatus             m_status;

    QList<int>           m_landUseDemand;
    QList<QList<double>> m_costMatrix;
    int *                m_landCounts;
    int                  m_maxCounts;
    QList<double>        m_wnb;
    int                  m_nTypes;

    QList<int *>      m_landCountInProcess;
    CA *              m_simThread;
    ValidationThread *m_valThread;
    QProcess *        m_process;
    int               m_curConfigNum;    // 用于线程交互
    int               m_curRepeatEpoch;  // 用于线程交互
    QRegExp           rx;
    QString           m_summaryLogName;  // 记录整体运行记录的ini文件名称
                                         /*                属性             */

    QThreadPool m_pool;
    int         m_numOfRuningTask;  // 当前正在/等待运行的任务个数
};

#endif  // BATCHCASIMDIALOG_H
