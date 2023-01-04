#include "commonrunnabletask.h"

CommonRunnableTask::CommonRunnableTask(char funType, CBatchCaSimConfig *cb, int rowInTable) {
    m_funType    = funType;
    m_cb         = cb;
    m_rowInTable = rowInTable;
}

void CommonRunnableTask::run() {
    if (m_funType == CommonRunnableTask::Sim) {
        emit signalStartRun(m_rowInTable);
        CA * caThread;
        if (Global::useV2) {
            caThread = m_cb->getCaMode() == "ACA" ? new ACCA_V2(0, "", false) : new CA_V2(0, "");
        } else {
            caThread = m_cb->getCaMode() == "ACA" ? new ACA(0, "") : new CA(0, "");
        }
        for (int i = 0; i < m_cb->getEpoches(); i++) {
            m_cb->setSimSavePath2Config(i + 1);
            caThread->setConfigPath(m_cb->getCaConfigPath());
            caThread->startSimulation();
            emit signalEpochFinished(m_rowInTable, i + 1, caThread->endIterTimes());  // 发送一轮的完成信号
        }
        caThread->freeImgFloatData();
        emit finished(m_rowInTable);
    } else {
    }
}
char CommonRunnableTask::Sim = '0';  // 用于模拟
char CommonRunnableTask::Val = '1';  // 用于验证
