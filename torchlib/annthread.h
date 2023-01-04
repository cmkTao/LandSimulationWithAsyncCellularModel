#ifndef ANNTHREAD_H
#define ANNTHREAD_H
#undef slots
#include <torch/torch.h>
#define slots Q_SLOTS

#include <QHash>

#include "alglib/TiffDataWrite.h"
#include "alglib/cqthread.h"
#include "entity/tifdataentity.h"
#include "torchlib/AnnStruct.h"
#include "torchlib/customdataset.h"
#include "utils/constValue.h"

class AnnThread : public CQThread {
    Q_OBJECT
public:
    AnnThread(QObject *parent);

    void          readDatas();
    void          filterDatas();
    void          sampleIndexOfDatas();
    CustomDataset getTrainDataSetAndAllTensors();
    void          writeProbs2Tif(float *datas, TifDataEntity *referTif, int bandNum, QString outPath);

    void trainModel();

    // ==== set and get ====
    void setSampleRatio(double tmp);
    //    double getSampleRatio();

    void setSampleMode(CVALUE::SAMPMODE tmp);
    //    CVALUE::SAMPMODE getSampleMode();

    void setHidden(int tmp = 32);
    void setEpochs(int tmp);

    void setLandPath1(QString tmp);
    void setLandPath2(QString tmp);
    void setDriveFactorDir(QString tmp);
    void setOutputPath(QString tmp);

private:
    double           sampleRatio;
    CVALUE::SAMPMODE sampleMode;
    QString          landPath1;
    QString          landPath2;
    QString          driveFactorDir;
    QString          outputPath;
    int              usedYear;
    int              numOfHiddenNeurons;

    int nTypes;
    int numOfClasses;
    int driveLen;
    int numOfValidPixels;

    QHash<int, QList<int>> land2index;
    QList<TifDataEntity *> tif_List;
    QHash<int, QList<int>> land2indexOfSample;
    QHash<int, int>        sampleOfLand;
    // index -> Tensor
    QHash<int, torch::Tensor> allTensorMap;

    int allDataSize;
    int trainDataSize;

    // ann config
    int    batchSize;
    size_t epochs;
};

#endif  // ANNTHREAD_H
