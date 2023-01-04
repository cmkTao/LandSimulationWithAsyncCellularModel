#include "cleandatathread.h"

CleanDataThread::CleanDataThread(
    QObject *parent, QString inputDir, QString outputDir, QString inputLandPath, int neiWidth)
    : CQThread(parent) {
    this->inputDir      = inputDir;
    this->outputDir     = outputDir;
    this->inputLandPath = inputLandPath;
    this->neiWidth      = neiWidth;
}

void CleanDataThread::run() {
    int                    neiWidth = this->neiWidth;
    int                    neiLen   = neiWidth * neiWidth - 1;
    int **                 offset   = MUTILS::getNeiOffset(neiWidth);
    QList<TifDataEntity *> tif_List;
    // 从1开始
    QMap<int, QList<int>> land2index;

    // ========= 读取数据 =============
    QString        path1        = this->inputLandPath;
    TifDataEntity *landTif      = new TifDataEntity(path1);
    int            nTypes       = landTif->getNTypes();
    int            numOfClasses = nTypes;
    QString        drive_dir    = this->inputDir;
    QString        out_dir      = this->outputDir;
    QDir           dir(drive_dir);
    QStringList    nameFilter;
    nameFilter << "*.tif";
    QStringList files = dir.entryList(nameFilter, QDir::Files | QDir::Readable, QDir::Name);
    QStringList drivePaths;
    for (QString f : files) {
        drivePaths << dir.filePath(f);
    }
    for (QString f : drivePaths) {
        TifDataEntity *tmp = new TifDataEntity(f);
        tif_List << tmp;
        qDebug() << f << tmp->getMax() << tmp->getMin() << tmp->getNoDataByBand();
        qDebug() << (tmp->getMax() >= tmp->getNoDataByBand() && tmp->getMin() <= tmp->getNoDataByBand());
    }
    int len = landTif->getNumOfAllPixels();
    sendMaxIterNum(len);
    qDebug() << len;
    int                rows = landTif->getRow();
    int                cols = landTif->getCol();
    QMap<QString, int> countMap;
    QMap<QString, int> inVCountMap;  // 合法性不一记录
    QMap<QString, int> zeroCountMap;
    QTime              time;
    time.start();
    for (int i = 0; i < len; i++) {
        // 此处发送信号将会导致界面卡死，尚未找到解决方法
        if (i % 20000 == 0) {
            signalSendProcess(i, len);
        }
        //        signalSendProcess(i, len);
        if (landTif->isValidLandPixels(i)) {
            for (TifDataEntity *tif : tif_List) {
                // 填充邻居平均值
                if (!tif->isValidPixels(i)) {
                    countMap[tif->getFilePath()] = countMap.value(tif->getFilePath(), 0) + 1;
                    int   count                  = 0;
                    float sum_                   = 0;
                    for (int j = 0; j < neiLen; j++) {
                        int r = i / cols + offset[j][0];
                        int c = i % cols + offset[j][1];
                        if (r < 0 || r >= rows || c < 0 || c >= cols) continue;
                        int index = r * cols + c;
                        if (tif->isValidPixels(index)) {
                            sum_ += tif->getValueByBandAndIndex(0, index);
                            count++;
                        }
                    }
                    double newValue = count == 0 ? tif->getMin() : sum_ / count;
                    tif->setValueByBandAndIndex(0, i, newValue);
                }
            }
        } else {
            for (TifDataEntity *tif : tif_List) {
                if (tif->isValidPixels(i)) {
                    inVCountMap[tif->getFilePath()] = inVCountMap.value(tif->getFilePath(), 0) + 1;
                    double newValue                 = tif->getNoDataValueByBand();
                    tif->setValueByBandAndIndex(0, i, newValue);
                }
            }
        }
    }
    qDebug() << zeroCountMap;

    int     timeDiff    = time.elapsed();
    float   f           = timeDiff / 1000.0;
    QString tr_timeDiff = QString::fromLocal8Bit("清洗耗时%1s").arg(f);
    sendStringMSG(QString::fromLocal8Bit("清洗耗时%1s").arg(f));
    qDebug() << tr_timeDiff;  // float->QString
    // 写会文件
    //    TIFTOOLS::
    qDebug() << "countMap: " << countMap;

    QDir outDir;
    if (!outDir.exists(out_dir)) {
        qDebug() << "bu cun zai ";
        outDir.mkdir(out_dir);
    } else {
        qDebug() << QString::fromLocal8Bit("删除所有文件");
        sendStringMSG(QString::fromLocal8Bit("删除所有文件"));
        if (outDir.path() != out_dir) {
            outDir.setPath(out_dir);
        }
        if (!outDir.removeRecursively()) {
            qDebug() << QString::fromLocal8Bit("删除失败");
            sendStringMSG(QString::fromLocal8Bit("删除失败"));
        } else {
            qDebug() << QString::fromLocal8Bit("删除成功");
            sendStringMSG(QString::fromLocal8Bit("删除成功"));
            outDir.mkdir(out_dir);
        }
    }

    for (int i = 0; i < files.size(); i++) {
        QString tmpPath = outDir.filePath(QString("c_%1").arg(files.at(i)));
        if (countMap.value(tif_List.at(i)->getFilePath(), 0) == 0
            && inVCountMap.value(tif_List.at(i)->getFilePath(), 0)) {
            qDebug() << QString::fromLocal8Bit("数据无噪点，按照原数据写回");
            sendStringMSG(QString::fromLocal8Bit("%1-->数据无噪点，按照原数据写回").arg(tif_List.at(i)->getFilePath()));
        } else {
            sendStringMSG(QString::fromLocal8Bit("%1-->数据噪点数量：%2_inv=%3")
                              .arg(tif_List.at(i)->getFilePath())
                              .arg(countMap.value(tif_List.at(i)->getFilePath(), 0))
                              .arg(inVCountMap.value(tif_List.at(i)->getFilePath(), 0)));
        }
        // 写入文件
        bool status = false;
        //        if (tif_List.at(i)->getDataType() == GDT_Float64) {
        //            status = TIFTOOLS::writeTIF2File<double>(
        //                tif_List.at(i)->getDoubleDataByBand(1), tif_List.at(i)->getDataType(), tmpPath, 1,
        //                tif_List.at(i));
        //        } else {
        //            status = TIFTOOLS::writeTIF2File<float>(
        //                tif_List.at(i)->getFloatDataByBand(1), tif_List.at(i)->getDataType(), tmpPath, 1,
        //                tif_List.at(i));
        //        }
        status = TIFTOOLS::writeTIF2File<float>(
            tif_List.at(i)->getFloatDataByBand(1), GDT_Float32, tmpPath, 1, tif_List.at(i));
        if (status) {
            qDebug() << tmpPath << QString::fromLocal8Bit("写入成功");
            sendStringMSG(QString::fromLocal8Bit("%1-->写入成功").arg(tmpPath));
        } else {
            qDebug() << QString::fromLocal8Bit("%1, 写入失败").arg(tmpPath);
            sendStringMSG(QString::fromLocal8Bit("%1-->写入失败").arg(tmpPath));
        }

        tif_List.at(i)->close();
    }
    tif_List.clear();
    landTif->close();
    emit isDone();
}
