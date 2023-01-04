/**
 * @projectName   qtmflus
 * @brief         摘要
 * 自定义QThread类，添加一些自定义的信号
 * @author        cmk
 * @date          2020-12-02
 */

#ifndef CQTHREAD_H
#define CQTHREAD_H

#include <QThread>
class CQThread : public QThread {
    Q_OBJECT
public:
    CQThread(QObject *parent);
signals:
    void isDone();  //处理完成信号
    // 发送字符串信息
    void signalSendMessage(QString);
    /**
     * @brief signalSendProcess
     * 发送进度
     * @param k 当前进度
     * @param maxP 最大进度值
     */
    void signalSendProcess(int k, int maxP);

    /**
     * @brief signalSendMaxIterNum
     * 发送最大进度值，用于外部设置progressBar的最大值
     * @param k
     */
    void signalSendMaxIterNum(int k);

protected:
    // 发送 字符串消息
    void sendStringMSG(const QString msg);
    void sendProcess(int k, int maxP);
    void sendMaxIterNum(int k);

    bool isToStop;
    bool isToPause;
};

#endif  // CQTHREAD_H
