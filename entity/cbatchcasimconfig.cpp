#include "cbatchcasimconfig.h"

CBatchCaSimConfig::CBatchCaSimConfig() {}

CBatchCaSimConfig::CBatchCaSimConfig(QString curDir, int epoches) {
    m_curDir           = curDir;
    m_epoches          = epoches;
    m_iterTimes        = 0;
    m_endIterTimes     = 0;
    m_meanEndIterTimes = 0;

    QDir dir(m_curDir);
    Q_ASSERT_X(dir.exists(), "文件类型错误", "curDir需要传递的目录不存在");
    m_curName              = dir.dirName();
    QString     filterName = "*.json";
    QStringList filter;
    filter << filterName;
    dir.setNameFilters(filter);
    QFileInfoList list = dir.entryInfoList();
    qDebug() << dir.entryList();
    /*  解析出ca配置文件和eval配置文件*/
    for (QFileInfo fi : list) {
        if (fi.fileName().startsWith("ca")) {
            if (m_caConfigPath == "") m_caConfigPath = fi.filePath();
        }

        if (fi.fileName().startsWith("eval")) {
            if (m_evalConfigPath == "") m_evalConfigPath = fi.filePath();
        }
    }
    if (m_caConfigPath == "") {
        m_isValidConfig = false;
    } else {
        m_isValidConfig = true;
        /* 获取保存文件的文件名前缀 */
        QString simSavePath = getSimSavePathFromConfig(m_caConfigPath);
        m_caMode            = getValueFromJsonByKey(m_caConfigPath, "caMode");
        m_acaRatio          = getValueFromJsonByKey(m_caConfigPath, "acaRatio").toDouble();
        m_iterTimes         = getMaxIterNumFromConfig(m_caConfigPath);
        initFromJsonFile();
        m_simSavePath = simSavePath;
        QFileInfo sfi(m_simSavePath);  // 默认保存到和配置文件相同的目录
        QDir      sDir      = sfi.dir();
        m_simSaveNamePrefix = sfi.baseName();
        if ("sim" != m_simSaveNamePrefix) {
            m_simSaveNamePrefix = "sim";
        }
        QString suffix    = sfi.suffix();
        QDir    configDir = MUTILS::getDirFromFilePath(m_caConfigPath);
        setSimSavePath2Config(m_caConfigPath, configDir.absoluteFilePath(m_simSaveNamePrefix + "." + suffix));
        for (int i = 1; i <= m_epoches; i++) {
            QString tmpName = QString("%1_%2").arg(m_simSaveNamePrefix).arg(i);
            tmpName         = QString("%1.%2").arg(tmpName).arg(suffix);
            m_simSavePathOfEachEpochList << configDir.absoluteFilePath(tmpName);
        }
        qDebug() << m_simSavePathOfEachEpochList;
        // 创建eval文件
        if (m_evalConfigPath == "") {
            m_evalConfigPath = sDir.absoluteFilePath("eval_config.json");
            if (!sDir.exists("eval_config.json")) {
                sDir.mkpath(sDir.absoluteFilePath("eval_config.json"));
            }
        }
        if (m_simSavePathOfEachEpochList.size() != 0)  // 不修改eval_config
            setValueToJsonByKey(m_evalConfigPath, "sim_path", m_simSavePathOfEachEpochList.join(" "));
    }
}

void CBatchCaSimConfig::print() {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    QString      configPath = m_caConfigPath;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    Json::StyledWriter sw;
    cout << "StyledWriter:" << endl;
    cout << sw.write(root) << endl << endl;
}

void CBatchCaSimConfig::setSimSavePath2Config(QString configPath, QString simSavePath) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    root["saveSimPath"] = Json::Value(simSavePath.toStdString());
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::setSimSavePath2Config(QString configPath, int epoch) {
    setSimSavePath2Config(configPath, m_simSavePathOfEachEpochList.at(epoch - 1));
}

void CBatchCaSimConfig::setSimSavePath2Config(int epoch) { setSimSavePath2Config(m_caConfigPath, epoch); }

QString CBatchCaSimConfig::getSimSavePathFromConfig(QString configPath, QString key) {
    return getValueFromJsonByKey(configPath, "saveSimPath");
}

QString CBatchCaSimConfig::getValueFromJsonByKey(QString configPath, QString key) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());

    if (reader.parse(in, root)) {
        return MUTILS::string2Qstring(root[key.toStdString()].asString());
    }
    in.close();
    return "";
}

void CBatchCaSimConfig::setValueToJsonByKey(QString key, QString value) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    QString      configPath = m_caConfigPath;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    QByteArray ba2;
    ba2.append(key);
    if (root.isMember(ba2.data())) {
        root[ba2.data()] = Json::Value(value.toStdString());
    }
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::setValueToJsonByKey(QString configPath, QString key, QString value) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    QByteArray ba2;
    ba2.append(key);
    if (root.isMember(ba2.data())) {
        root[ba2.data()] = Json::Value(value.toStdString());
    }
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::setValueToJsonByKey(QString key, int value) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    QString      configPath = m_caConfigPath;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    QByteArray ba2;
    ba2.append(key);
    if (root.isMember(ba2.data())) {
        root[ba2.data()] = Json::Value(value);
    }
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::setValueToJsonByKey(QString key, double value) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    QString      configPath = m_caConfigPath;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    QByteArray ba2;
    ba2.append(key);
    root[ba2.data()] = Json::Value(value);
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::setValueToJsonByKey(QString key, QList<QList<double>> value) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    QString      configPath = m_caConfigPath;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    QByteArray ba2;
    ba2.append(key);
    char* ckey = ba2.data();
    if (root.isMember(ba2.data())) {
        for (int i = 0; i < value.size(); i++) {
            for (int j = 0; j < value.at(i).size(); j++) {
                root[ckey][i][j] = value[i][j];
            }
        }
    }
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::setValueToJsonByKey(QString key, QList<double> value) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    QString      configPath = m_caConfigPath;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    QByteArray ba2;
    ba2.append(key);
    char* ckey = ba2.data();
    if (root.isMember(ba2.data())) {
        for (int i = 0; i < value.size(); i++) {
            root[ckey][i] = value.at(i);
        }
    }
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::setValueToJsonByKey(QString key, QList<int> value) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    QString      configPath = m_caConfigPath;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    QByteArray ba2;
    ba2.append(key);
    char* ckey = ba2.data();
    if (root.isMember(ba2.data())) {
        for (int i = 0; i < value.size(); i++) {
            root[ckey][i] = value.at(i);
        }
    }
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::updateToJsonFile() {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    QString      configPath = m_caConfigPath;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();

    /* 重写写入配置文件 */
    root["endDiffValue"]                  = Json::Value(m_endDiffValue);
    root["simConfig"]["maxIterNum"]       = Json::Value(m_maxIter);
    root["simConfig"]["neighboorhoodOdd"] = Json::Value(m_neiOdd);

    // 写数组
    for (int i = 0; i < m_landUseDemand.size(); i++) {
        root["landUseDemand"][i]        = Json::Value(m_landUseDemand.at(i));
        root["weightOfNeighborhood"][i] = Json::Value(m_wnb.at(i));
        for (int j = 0; j < m_landUseDemand.size(); j++) {
            root["costMatrix"][i][j] = Json::Value(m_costMatrix[i][j]);
        }
    }

    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(configPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::saveToOther(QString filePath) { saveConfigToOther(m_caConfigPath, filePath); }

void CBatchCaSimConfig::saveConfigToOther(QString configPath, QString otherPath) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(otherPath.toStdString());
    os << sw.write(root);
    os.close();
}

void CBatchCaSimConfig::saveEvalToOther(QString filePath) { saveConfigToOther(m_evalConfigPath, filePath); }

int CBatchCaSimConfig::getMaxIterNumFromConfig(QString configPath) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    ifstream     in(configPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(configPath).toLocal8Bit().data());

    if (reader.parse(in, root)) {
        return root["simConfig"]["maxIterNum"].asInt();
    }
    in.close();
    return 0;
}

void CBatchCaSimConfig::resetSimPath2Config() { setSimSavePath2Config(m_caConfigPath, m_simSavePath); }

bool CBatchCaSimConfig::isValid() const { return m_isValidConfig; }

QList<QString> CBatchCaSimConfig::getSimSavePathOfEachEpochList() { return m_simSavePathOfEachEpochList; }

QString CBatchCaSimConfig::getCaConfigPath() const { return m_caConfigPath; }

int CBatchCaSimConfig::getEpoches() const { return m_epoches; }

QString CBatchCaSimConfig::getCaMode() const { return m_caMode; }

int CBatchCaSimConfig::getIterTimes() const { return m_iterTimes; }

QString CBatchCaSimConfig::getCurDir() const { return m_curDir; }

QString CBatchCaSimConfig::getEvalConfigPath() const { return m_evalConfigPath; }

QString CBatchCaSimConfig::genEvalConfig(QString endTifPath) {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    ifstream     in(m_evalConfigPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(m_evalConfigPath).toLocal8Bit().data());
    root["start_path"] = Json::Value(getValueFromJsonByKey(m_caConfigPath, "landUsePath").toStdString());
    root["true_path"]  = Json::Value(endTifPath.toStdString());
    root["sim_path"]   = Json::Value(m_simSavePathOfEachEpochList.join(" ").toStdString());
    Json::StyledWriter sw;

    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;

    ofstream os;
    os.open(m_evalConfigPath.toStdString());
    os << sw.write(root);
    in.close();
    return "";
}

QString CBatchCaSimConfig::getCurConfigDirName() {
    QFileInfo fi(m_curDir);
    return fi.fileName();
}

int CBatchCaSimConfig::getEndIterTimes() const { return m_endIterTimes; }

void CBatchCaSimConfig::setEndIterTimes(int endIterTimes) { m_endIterTimes = endIterTimes; }

int CBatchCaSimConfig::getMeanIterTimes() {
    m_meanEndIterTimes = m_endIterTimes / m_epoches;
    return m_meanEndIterTimes;
}

void CBatchCaSimConfig::setMeanEndIterTimes(int meanEndIterTimes) { m_meanEndIterTimes = meanEndIterTimes; }

int CBatchCaSimConfig::getMeanEndIterTimes() const { return m_meanEndIterTimes; }

void CBatchCaSimConfig::initFromJsonFile() {
    Json::Reader reader;
    Json::Value  root, tempVal;
    int          nSize;
    ifstream     in(m_caConfigPath.toStdString(), ios::binary);
    bool         status;
    Q_ASSERT_X(in.is_open(), "文件打开失败", QString("文件%1不存在").arg(m_caConfigPath).toLocal8Bit().data());
    reader.parse(in, root);
    in.close();
    tempVal = root["landUseDemand"];
    nSize   = tempVal.size();
    for (int i = 0; i < nSize; i++) {
        m_landUseDemand.append(tempVal[i].asInt());
    }

    tempVal = root["weightOfNeighborhood"];
    for (int i = 0; i < nSize; i++) {
        m_wnb.append(tempVal[i].asDouble());
    }

    tempVal = root["costMatrix"];
    for (int i = 0; i < nSize; i++) {
        QList<double> temp;
        for (int j = 0; j < nSize; j++) {
            temp.append(tempVal[i][j].asDouble());
        }
        m_costMatrix.append(temp);
    }
    m_endDiffValue = root["endDiffValue"].asInt();
    m_maxIter      = root["simConfig"]["maxIterNum"].asInt();
    m_neiOdd       = root["simConfig"]["neighboorhoodOdd"].asInt();
    //    Json::StyledWriter sw;
    //    cout << "StyledWriter:" << endl;
    //    cout << sw.write(root) << endl << endl;
}

QString CBatchCaSimConfig::getCurName() const { return m_curName; }

double CBatchCaSimConfig::getCaRatio() const { return m_acaRatio; }

void CBatchCaSimConfig::setCaRatio(double caRatio) { m_acaRatio = caRatio; }

int CBatchCaSimConfig::getNeiOdd() const { return m_neiOdd; }

void CBatchCaSimConfig::setNeiOdd(int neiOdd) { m_neiOdd = neiOdd; }

int CBatchCaSimConfig::getEndDiffValue() const { return m_endDiffValue; }

void CBatchCaSimConfig::setEndDiffValue(int endDiffValue) { m_endDiffValue = endDiffValue; }

int CBatchCaSimConfig::getMaxIter() const { return m_maxIter; }

void CBatchCaSimConfig::setMaxIter(int maxIter) { m_maxIter = maxIter; }

QList<double> CBatchCaSimConfig::getWnb() const { return m_wnb; }

void CBatchCaSimConfig::setWnb(const QList<double>& wnb) { m_wnb = wnb; }

QList<QList<double>> CBatchCaSimConfig::getCostMatrix() const { return m_costMatrix; }

void CBatchCaSimConfig::setCostMatrix(const QList<QList<double>>& costMatrix) { m_costMatrix = costMatrix; }

QList<int> CBatchCaSimConfig::getLandUseDemand() const { return m_landUseDemand; }

void CBatchCaSimConfig::setLandUseDemand(const QList<int>& landUseDemand) { m_landUseDemand = landUseDemand; }
