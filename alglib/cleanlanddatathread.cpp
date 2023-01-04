#include "cleanlanddatathread.h"

CleanLandDataThread::CleanLandDataThread(QObject *parent, QString startTifPath, QString targetTifPath, QString savePath)
    : CQThread(parent) {
    this->startTifPath  = startTifPath;
    this->targetTifPath = targetTifPath;
    this->savePath      = savePath;
}

void CleanLandDataThread::run() {
    int               neiWidth        = 9;
    int               neiLen          = neiWidth * neiWidth - 1;
    int **            offset          = MUTILS::getNeiOffset(neiWidth);
    TifDataEntity *   startTif        = new TifDataEntity(startTifPath);
    TifDataEntity *   targetTif       = new TifDataEntity(targetTifPath);
    int               len             = targetTif->getNumOfAllPixels();
    int               rows            = startTif->getRow();
    int               cols            = startTif->getCol();
    int               fixValidCount   = 0;
    int               fixInValidCount = 0;
    QMap<double, int> map;
    int               maxCount = 0;
    float             maxCode  = 1;
    for (int i = 0; i < len; i++) {
        //        if (i % 20000 == 0) {
        //            signalSendProcess(i, len);
        //        }
        maxCount = 0;
        maxCode  = 0;
        // 如果target是合法，且start不是合法像素
        // 采用start 邻域中类型最多的作为分配类型
        if (!startTif->isValidLandPixels(i) && targetTif->isValidLandPixels(i)) {
            map.clear();
            for (int j = 0; j < neiLen; j++) {
                int r = i / cols + offset[j][0];
                int c = i % cols + offset[j][1];
                if (r < 0 || r >= rows || c < 0 || c >= cols) continue;
                int index = r * cols + c;
                if (startTif->isValidLandPixels(index)) {
                    double key = startTif->getValueByBandAndIndex(0, index);
                    map[key]   = map[key] + 1;
                    if (map[key] > maxCount) {
                        maxCode  = key;
                        maxCount = map[key];
                    }
                }
            }
            fixValidCount++;
            startTif->setValueByBandAndIndex(0, i, maxCode);
        }
        // 如果target非法，start合法，则将start改为非法
        if (startTif->isValidLandPixels(i) && !targetTif->isValidLandPixels(i)) {
            startTif->setValueByBandAndIndex(0, i, startTif->getNoDataValueByBand());
            fixInValidCount++;
        }
    }
    TIFTOOLS::writeTIF2File<unsigned char>(startTif->getByteDataByBand(1), GDT_Byte, savePath, 1, startTif);
    sendStringMSG(
        QString::fromLocal8Bit("%1个valid像元被修复, %2个inValid像元被修复").arg(fixValidCount).arg(fixInValidCount));
    startTif->close();
    targetTif->close();
    emit isDone();
}
