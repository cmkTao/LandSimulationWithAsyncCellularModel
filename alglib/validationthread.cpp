#include "validationthread.h"

ValidationThread::ValidationThread(QObject *parent) : QThread(parent) {
    m_startTif = NULL;
    m_endTif   = NULL;
    qRegisterMetaType<QList<QList<double>>>("Pos");
}

void ValidationThread::run() { startValidation(); }

bool ValidationThread::isFileExists(QString path) {
    QFileInfo fi(path);
    return fi.exists();
}

void ValidationThread::loadFromConfig() {
    Json::Reader reader;
    Json::Value  root, tempVal;
    bool         res;
    QByteArray   qByteArray = m_evalConfigPath.toUtf8();
    char *       path       = qByteArray.data();
    ifstream     in(path, ios::binary);

    if (!in.is_open()) {
        qDebug() << "Error opening file\n";
        return;
    }

    if (!reader.parse(in, root)) {
        qDebug() << "fail to parse json file" << endl;
        in.close();
        return;
    }

    m_startTifPath = MUTILS::string2Qstring(root["start_path"].asString());
    m_endTifPath   = MUTILS::string2Qstring(root["true_path"].asString());

    m_startTif    = new TifDataEntity(m_startTifPath);
    m_endTif      = new TifDataEntity(m_endTifPath);
    m_simPathList = MUTILS::string2Qstring(root["sim_path"].asString()).split(" ");
    in.close();
}

void ValidationThread::startValidation() {
    loadFromConfig();
    QList<QList<int>>    transMatrix;
    TifDataEntity *      simTif     = NULL;
    int                  nTypes     = m_endTif->getNTypes();
    int                  landCounts = m_endTif->getSumPixels();  // 获取真实数据有效像元总数
    double               OA, Kappa, Fom, pe, p0;
    QList<QList<double>> valRes;
    QList<double>        meanRes({0, 0, 0});
    for (QString simPath : m_simPathList) {
        if (!isFileExists(simPath)) {  // 不存在则跳过
            continue;
        }
        // oa, kappa, fom
        QList<double> list({0, 0, 0});
        simTif                    = new TifDataEntity(simPath);
        transMatrix               = simTif->getTransitionMatrix(m_endTif);
        double sim_correct_counts = 0.0;  // 模拟正确的像素数量
        pe                        = 0.0;
        for (int i = 0; i < nTypes; i++) {
            sim_correct_counts += transMatrix[i][i];
            //            int c1 = 0;
            //            int c2 = 0;
            //            for (int k = 0; k++; k < nTypes) {
            //                c1 += transMatrix[i][k];
            //                c2 += transMatrix[k][i];
            //            }
            //            pe += c1 * c2;
            //            qDebug() << QString("%1 * %2 = %3")
            //                            .arg(m_endTif->getLandCountByLandCode(i + 1))
            //                            .arg(simTif->getLandCountByLandCode(i + 1))
            //                            .arg(m_endTif->getLandCountByLandCode(i + 1) *
            //                            simTif->getLandCountByLandCode(i + 1));

            pe += (long long)((long long)m_endTif->getLandCountByLandCode(i + 1)
                              * (long long)simTif->getLandCountByLandCode(i + 1));
            //            pe += m_endTif->getLandCountByLandCode(i + 1) * simTif->getLandCountByLandCode(i + 1);
        }
        p0 = OA = sim_correct_counts / landCounts;
        pe /= (long long)((long long)landCounts * (long long)landCounts);
        Kappa   = (p0 - pe) / (1 - pe);
        Fom     = calFom(m_startTif, m_endTif, simTif);
        list[0] = OA;
        list[1] = Kappa;
        list[2] = Fom;
        meanRes[0] += OA;
        meanRes[1] += Kappa;
        meanRes[2] += Fom;
        valRes.append(list);

        // 释放内存
        simTif->close();
        delete simTif;
    }
    meanRes[0] /= valRes.size();
    meanRes[1] /= valRes.size();
    meanRes[2] /= valRes.size();
    MUTILS::truncateDouble(meanRes[0], 5);
    MUTILS::truncateDouble(meanRes[1], 5);
    MUTILS::truncateDouble(meanRes[2], 5);
    valRes.append(meanRes);

    // 释放内存
    m_startTif->close();
    delete m_startTif;
    m_endTif->close();
    delete m_endTif;
    //    qDebug() << valRes;
    emit isDone(valRes);
}

double ValidationThread::calFom(TifDataEntity *startTif, TifDataEntity *endTif, TifDataEntity *simTif) {
    int    allPixelNum = endTif->getNumOfAllPixels();
    double A           = 0.0;  // 实际变化，模拟却没变（错误）
    double B           = 0.0;  // 实际变化，模拟也变化了，且变化为正确类型（正确）
    double C           = 0.0;  // 实际变化，模拟也变化了，且变化为错误类型（错误）
    double D           = 0.0;  // 实际没变，但模拟却变化了（错误）
    for (int i = 0; i < allPixelNum; i++) {
        // 统一位置，像元没有全部合法则跳过
        if (!startTif->isValidLandPixels(i) || !endTif->isValidLandPixels(i) || !simTif->isValidLandPixels(i)) {
            continue;
        }
        int startType = startTif->getValueByBandAndIndex(0, i);
        int trueType  = endTif->getValueByBandAndIndex(0, i);
        int simType   = simTif->getValueByBandAndIndex(0, i);
        if (startType == trueType) {           // 实际没变的
            if (simType != startType) D += 1;  // 模拟变化了
        }
        if (startType != trueType) {           // 实际变化的
            if (simType == startType) A += 1;  //实际变化，模拟却没变（错误）
            if (startType != simType && simType == trueType)
                B += 1;  // 实际变化，模拟也变化了，且变化为正确类型（正确）
            if (startType != simType && simType != trueType) C += 1;  //实际变化，模拟也变化了，且变化为错误类型（错误）
        }
    }
    return B / (A + B + C + D);
}

void ValidationThread::setEvalConfigPath(const QString &evalConfigPath) { m_evalConfigPath = evalConfigPath; }

void ValidationThread::test() { startValidation(); }
