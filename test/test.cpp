
#undef slots
#include <torch/torch.h>
#define slots Q_SLOTS
#include <entity/tifdataentity.h>
#include <torch/torch.h>
#include <torchlib/customdataset.h>
#include <utils/tifTools.h>

#include <iostream>
#include <typeinfo>

#include "test.h"
using namespace std;

void TEST::testType() {
    int   a     = 10;
    char *p     = NULL;
    char  str[] = "hello world";
    cout << typeid(p).name() << endl;
    cout << typeid(str).name() << endl;
    cout << typeid(a).name() << endl;
}

void TEST::testTifWrite() {
    QString path1 = "E:/project/c/qt_project/test_demo/12n.tif";
    QString path2 = "E:/project/c/qt_project/test_demo/12n_write.tif";

    TifDataEntity *tifData = new TifDataEntity(path1);
    bool           status  = TIFTOOLS::writeTIF2File(tifData->getUCharData(), GDT_Byte, path2, 1, tifData);
    if (status) {
        qDebug() << QString::fromLocal8Bit("写入成功");
    } else {
        qDebug() << QString::fromLocal8Bit("写入失败");
    }
}

void TEST::testSyncSim() {
    //    QFile::remove("E:/project/c/qt_project/test_demo/dg_datas/sim_file/dg_sim.tif");
    CA *ca = new CA(0, "E:/project/c/qt_project/test_demo/dg_demo/ca_config.json");
    ca->start();
}

void TEST::testShark() { /*Data<RealVector> data(1000, RealVector(5));*/
}

void TEST::testTorch() {
    int                    usedYear         = 1;
    QString                sampleMode       = "u";
    double                 sampleRatio      = 0.1;
    int                    numOfValidPixels = 0;
    QList<TifDataEntity *> tif_List;
    // 从1开始, 每种土地对应的偏移量
    QMap<int, QList<int>> land2index;

    //    // ========= 读取数据 =============
    QString path1 = "E:/project/c/qt_project/test_demo/hgs_datas/12n.tif";
    QString path2 = "E:/project/c/qt_project/test_demo/hgs_datas/17n.tif";
    tif_List << new TifDataEntity(path1);
    int nTypes       = tif_List.at(0)->getNTypes();
    int numOfClasses = nTypes;
    if (usedYear == 2) {
        tif_List << new TifDataEntity(path2);
        numOfClasses = nTypes * nTypes;
    }

    QString     drive_dir = "E:/project/c/qt_project/test_demo/hgs_datas/drive_factor/";
    QDir        dir(drive_dir);
    QStringList nameFilter;
    nameFilter << "*.tif";
    QStringList files = dir.entryList(nameFilter, QDir::Files | QDir::Readable, QDir::Name);
    QStringList drivePaths;
    for (QString f : files) {
        drivePaths << dir.filePath(f);
    }
    int           driveLen   = drivePaths.size();
    torch::Tensor train_data = torch::zeros({1, driveLen});
    torch::Tensor label_data;
    for (QString f : drivePaths) {
        tif_List << new TifDataEntity(f);
    }

    //    // =========== 过滤非法数据 ===========
    if (usedYear == 2) {
        for (int i = 0; i < numOfClasses; i++) {
            land2index[i] = QList<int>{};
        }
    }
    int  nap = tif_List.at(0)->getNumOfAllPixels();
    bool validFlag;
    for (int i = 0; i < nap; i++) {
        validFlag = true;
        // 所有图层合法的像素位置
        for (int j = 0; j < tif_List.size(); j++) {
            if (!tif_List.at(j)->isValidPixels(i)) {
                validFlag = false;
                break;
            }
        }

        if (validFlag) {
            numOfValidPixels++;
            if (usedYear == 2) {
                int s1 = tif_List.at(0)->getValueByBandAndIndex(0, i);
                int s2 = tif_List.at(1)->getValueByBandAndIndex(0, i);
                land2index[nTypes * (s1 - 1) + s2] << i;
            } else {
                land2index[tif_List.at(0)->getValueByBandAndIndex(0, i)] << i;
            }
        }
    }
    qDebug() << land2index.keys();

    // ============ 采样数据 ==========
    int                   numOfAllSamples = numOfValidPixels * sampleRatio;
    QMap<int, QList<int>> land2indexOfSample;
    QMap<int, int>        sampleOfLand;

    //    // 获取每种土地的采样
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    for (int i = 1; i <= numOfClasses; i++) {
        if (sampleMode == "u") {
            sampleOfLand[i] = numOfAllSamples / land2index.size();
        } else {
            sampleOfLand[i] = (land2index[i].size() * 1.0 / numOfValidPixels) * numOfAllSamples;
        }
        std::shuffle(land2index[i].begin(), land2index[i].end(), std::default_random_engine(seed));
        int mins = MUTILS::getMin<int>(land2index[i].size(), sampleOfLand[i]);
        qDebug() << QString("land: %1, valid pixels %2, sample %3, final sample %4")
                        .arg(i)
                        .arg(land2index[i].size())
                        .arg(sampleOfLand[i])
                        .arg(mins);
        QList<int> nl(land2index[i].begin(), land2index[i].begin() + mins);
        land2indexOfSample[i] = nl;
    }
    qDebug() << land2indexOfSample.values();
    //    return;

    // === TODO 数据转为Tensor ===
    // index-Tensor
    auto                                  custom_dataset = CustomDataset();
    QMap<int, torch::Tensor>              allTensorMap;
    QMap<int, QList<int>>::const_iterator cb = land2index.cbegin();
    QMap<int, QList<int>>::const_iterator ce = land2index.cend();
    QMap<int, torch::Tensor>              sampleTensorMap;
    QList<int>                            sampleLabel;
    float *                               tmp;
    int                                   i;
    for (; cb != ce; cb++) {
        for (int index : cb.value()) {
            tmp = new float[driveLen];
            for (i = 0; i < driveLen; i++) {
                TifDataEntity *tde = tif_List.at(i + usedYear);
                // 标准化
                tmp[i] = (tde->getValueByBandAndIndex(0, index) - tde->getMin()) / tde->getMax();
            }
            tmp[i]              = cb.key();
            auto ts             = torch::from_blob(tmp, {1, driveLen}).toType(torch::kFloat32);
            allTensorMap[index] = ts.clone();
            // 将数据插入自定义数据集中
            custom_dataset.insertOneFloatFeatureAndIntLabel(tmp, driveLen, cb.key());
        }
    }
    cb = land2indexOfSample.cbegin();
    ce = land2indexOfSample.cend();
    for (; cb != ce; cb++) {
        for (int index : cb.value()) {
            custom_dataset.insertOneTensorData(allTensorMap[index].clone(), torch::full({1}, cb.key()));
        }
    }

    // ANN训练     TODO
    // ANN预测     TODO
    // ANN结果保存  TODO
}

void TEST::testClean() {
    int   usedYear         = 1;
    int   numOfValidPixels = 0;
    int   neiWidth         = 3;
    int   neiLen           = neiWidth * neiWidth - 1;
    int **offset           = MUTILS::getNeiOffset(neiWidth);
    //    return;
    QList<TifDataEntity *> tif_List;
    // 从1开始
    QMap<int, QList<int>> land2index;

    // ========= 读取数据 =============
    QString        path1        = "E:/project/c/qt_project/test_demo/dg_datas/dg2001coor.tif";
    QString        path2        = "E:/project/c/qt_project/test_demo/hgs_datas/17n.tif";
    TifDataEntity *landTif      = new TifDataEntity(path1);
    int            nTypes       = landTif->getNTypes();
    int            numOfClasses = nTypes;
    if (usedYear == 2) {
        tif_List << new TifDataEntity(path2);
        numOfClasses = nTypes * nTypes;
    }
    QString     drive_dir = "E:/project/c/qt_project/test_demo/dg_datas/drive_factor";
    QString     out_dir   = "E:/project/c/qt_project/test_demo/dg_datas/c_drive_factor";
    QDir        dir(drive_dir);
    QStringList nameFilter;
    nameFilter << "*.tif";
    QStringList files = dir.entryList(nameFilter, QDir::Files | QDir::Readable, QDir::Name);
    QStringList drivePaths;
    for (QString f : files) {
        drivePaths << dir.filePath(f);
    }
    for (QString f : drivePaths) {
        TifDataEntity *tmp = new TifDataEntity(f);

        tif_List << tmp;
        qDebug() << f << tmp->getMax() << tmp->getMin();
    }
    int len = landTif->getNumOfAllPixels();
    qDebug() << len;
    int                rows = landTif->getRow();
    int                cols = landTif->getCol();
    QMap<QString, int> countMap;
    QTime              time;
    time.start();
    for (int i = 0; i < len; i++) {
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
                    //                    qDebug() << tif->getValueByBandAndIndex(0, i);
                }
            }
        } else {
            for (TifDataEntity *tif : tif_List) {
                double newValue = tif->getNoDataValueByBand();
                tif->setValueByBandAndIndex(0, i, newValue);
            }
        }
    }

    int     timeDiff    = time.elapsed();
    float   f           = timeDiff / 1000.0;
    QString tr_timeDiff = QString::fromLocal8Bit("初始化细胞用时：%1s").arg(f);
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
        if (outDir.path() != out_dir) {
            outDir.setPath(out_dir);
        }
        if (!outDir.removeRecursively()) {
            qDebug() << QString::fromLocal8Bit("删除失败");
        } else {
            qDebug() << QString::fromLocal8Bit("删除成功");
            outDir.mkdir(out_dir);
        }
    }

    for (int i = 0; i < files.size(); i++) {
        QString tmpPath = outDir.filePath(QString("c_%1").arg(files.at(i)));
        if (countMap.value(tif_List.at(i)->getFilePath(), 0) == 0) {
            qDebug() << QString::fromLocal8Bit("数据无噪点，按照原数据写回");
        }
        bool status = TIFTOOLS::writeTIF2File<float>(
            tif_List.at(i)->getFloatDataByBand(1), GDT_Float32, tmpPath, 1, tif_List.at(i));
        if (status) {
            qDebug() << tmpPath << QString::fromLocal8Bit("写入成功");
        } else {
            qDebug() << tmpPath << QString::fromLocal8Bit("写入失败");
        }

        // ============ 写入方式二 ============
        //        size_t ii, j, k;

        //        /// <生成tiff文件>
        //        TiffDataWrite pwrite;
        //        bool brlt = pwrite.init(tmpPath.toStdString().c_str(), tif_List.at(i)->getRow(),
        //        tif_List.at(i)->getCol(), 1,
        //            tif_List.at(i)->getTransFromData(), tif_List.at(i)->getProj(), GDT_Float32,
        //            tif_List.at(i)->getNoDataByBand());

        //        if (!brlt) {
        //            cout << "write init error!" << endl;
        //            return;
        //        }
        //        float _val = 0;
        //        for (ii = 0; ii < pwrite.rows(); ii++) {
        //            for (j = 0; j < pwrite.cols(); j++) {
        //                for (k = 0; k < pwrite.bandnum(); k++) {
        //                    int datalen;
        //                    datalen = k * pwrite.rows() * pwrite.cols() + ii * pwrite.cols() + j;
        //                    if (tif_List.at(i)->isValidPixels(datalen)) {
        //                        _val = tif_List.at(i)->getValueByBandAndIndex(0, datalen);
        //                    } else {
        //                        _val = tif_List.at(i)->getNoDataByBand();
        //                    }
        //                    pwrite.write(ii, j, k, &_val);
        //                }
        //            }
        //        }
        //        cout << tmpPath.toStdString() << "write success!" << endl;
        //        pwrite.close();

        tif_List.at(i)->close();
    }
    tif_List.clear();
    landTif->close();
}

void TEST::testAnn() {
    //    AnnThread *annT = new AnnThread(0);
    //    annT->setLandPath1("E:/project/c/qt_project/test_demo/dg_datas/dg2001coor.tif");
    //    //    annT->setLandPath2("E:/project/c/qt_project/test_demo/dg_datas/dg2006true.tif");
    //    annT->setDriveFactorDir("E:/project/c/qt_project/test_demo/dg_datas/drive_factor/");
    //    annT->setOutputPath("E:/project/c/qt_project/test_demo/dg_datas/mp.tif");
    //    annT->setSampleMode(CVALUE::SAMPMODE::U);
    //    annT->setSampleRatio(0.1);
    //    annT->setHidden(32);
    //    annT->setEpochs(100);

    //    annT->trainModel();
}
