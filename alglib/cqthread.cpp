#include "cqthread.h"

#include <QThread>
CQThread::CQThread(QObject *parent) : QThread(parent) {}

void CQThread::sendStringMSG(const QString msg) { emit signalSendMessage(msg); }

void CQThread::sendProcess(int k, int maxP) { emit signalSendProcess(k, maxP); }

void CQThread::sendMaxIterNum(int k) { emit signalSendMaxIterNum(k); }
