#include "config.h"
namespace DEFAULTCONFIG {

bool useOfficalFlusVersion = false;

QString                annDefaultConfigPath = "";
QStringList            caDefaultConfigPath;
QString                evalDefaultConfigPath = "";
QString landConfigPath = "";
bool                   useOneYear            = true;
QMap<QString, QString> namePathMap;
struct TifPathConfig   tifPathConfig;
QString                DEFAULT_CONFIG = DEFAULT_CONFIG1;

QStringList TifPathConfig::getNoEmptyPathList() {
    QStringList combTexts;
    if (MUTILS::isFileExist(startTifPath)) {
        QFileInfo fi = QFileInfo(startTifPath);
        combTexts << fi.fileName();
        namePathMap.insert(fi.fileName(), startTifPath);
    }
    if (MUTILS::isFileExist(endTifPath)) {
        QFileInfo fi = QFileInfo(endTifPath);
        combTexts << fi.fileName();
        namePathMap.insert(fi.fileName(), endTifPath);
    }
    if (MUTILS::isFileExist(probsTifPath)) {
        QFileInfo fi = QFileInfo(probsTifPath);
        combTexts << fi.fileName();
        namePathMap.insert(fi.fileName(), probsTifPath);
    }
    for (QString tmp : simTifPath) {
        if (MUTILS::isFileExist(tmp)) {
            QFileInfo fi = QFileInfo(tmp);
            combTexts << fi.fileName();
            namePathMap.insert(fi.fileName(), tmp);
        }
    }
//    qDebug() << combTexts;
    return combTexts;
}

QStringList TifPathConfig::getDiffPair() {
    QStringList combTexts;
    if (MUTILS::isFileExist(startTifPath) && MUTILS::isFileExist(endTifPath)) {
        QString f1 = getFileNameFromPath(startTifPath);
        QString f2 = getFileNameFromPath(endTifPath);
        insertKeyValueSafe(f1, startTifPath);
        insertKeyValueSafe(f2, endTifPath);
        combTexts << f1 + "-" + f2;
    }
    for (QString tmp : simTifPath) {
        if (MUTILS::isFileExist(endTifPath) && MUTILS::isFileExist(tmp)) {
            QString f1 = getFileNameFromPath(endTifPath);
            QString f2 = getFileNameFromPath(tmp);
            insertKeyValueSafe(f1, endTifPath);
            insertKeyValueSafe(f2, tmp);
            combTexts << f1 + "-" + f2;
        }
        if (MUTILS::isFileExist(startTifPath) && MUTILS::isFileExist(tmp)) {
            QString f1 = getFileNameFromPath(startTifPath);
            QString f2 = getFileNameFromPath(tmp);
            insertKeyValueSafe(f1, startTifPath);
            insertKeyValueSafe(f2, tmp);
            combTexts << f1 + "-" + f2;
        }
    }

    return combTexts;
}

QString TifPathConfig::getFileNameFromPath(QString path) {
    QFileInfo fi = QFileInfo(path);
    return fi.fileName();
}

void insertKeyValueSafe(QString key, QString value) {
    if (namePathMap.contains(key)) {
        namePathMap[key] = value;
    } else {
        namePathMap.insert(key, value);
    }
}

bool loadTifPathFromJson() {
    QString      jsonPath;
    Json::Reader reader;
    Json::Value  root, tempVal, root2;
    int          nSize;
    jsonPath = annDefaultConfigPath;
    ifstream in(jsonPath.toStdString(), ios::binary);
    bool     status;
    if (!in.is_open()) {
        QMessageBox::critical(nullptr, "Error!", QString("Can not open file %1 ann").arg(jsonPath));
        status = false;
        return false;
    }
    if (reader.parse(in, root)) {
        tifPathConfig.probsTifPath = MUTILS::string2Qstring(root["save_path"].asString());
    }
    in.close();
    jsonPath = evalDefaultConfigPath;
    in       = ifstream(jsonPath.toStdString(), ios::binary);
    if (!in.is_open()) {
        QMessageBox::critical(nullptr, "Error!", QString("Can not open file %1 eval").arg(jsonPath));
        status = false;
        return false;
    }
    if (reader.parse(in, root2)) {
        tifPathConfig.startTifPath = MUTILS::string2Qstring(root2["start_path"].asString());
        tifPathConfig.endTifPath   = MUTILS::string2Qstring(root2["true_path"].asString());
    }
    in.close();
    tifPathConfig.simTifPath.clear();
    for (QString tmp : caDefaultConfigPath) {
        jsonPath = tmp;
        in       = ifstream(jsonPath.toStdString(), ios::binary);
        if (!in.is_open()) {
            QMessageBox::critical(nullptr, "Error!", QString("Can not open file %1").arg(jsonPath));
            status = false;
            return false;
        }
        if (reader.parse(in, root2)) {
            tifPathConfig.simTifPath << MUTILS::string2Qstring(root2["saveSimPath"].asString());
        }
        in.close();
    }
    qDebug() << tifPathConfig.startTifPath;
    qDebug() << tifPathConfig.endTifPath;
    qDebug() << tifPathConfig.probsTifPath;
    qDebug() << tifPathConfig.simTifPath;
    return true;
}

void setDefaultConfigPath() { DEFAULT_CONFIG = useOneYear ? DEFAULT_CONFIG1 : DEFAULT_CONFIG2; }

bool loadDefaultConfigPath(QString path) {
    DEFAULTCONFIG::DEFAULT_CONFIG = useOneYear ? DEFAULTCONFIG::DEFAULT_CONFIG1 : DEFAULTCONFIG::DEFAULT_CONFIG2;
    if (path == "") {
        path = DEFAULTCONFIG::DEFAULT_CONFIG;
    }
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can't open the file!" << DEFAULTCONFIG::DEFAULT_CONFIG << endl;
        QMessageBox::critical(nullptr, "TIPS!", "Can't open the file: " + DEFAULTCONFIG::DEFAULT_CONFIG);
        return false;
    }
    caDefaultConfigPath.clear();
//    DEFAULTCONFIG::caDefaultConfigPath = QSettingTools::getVariantFromIniFile(path, "sim", "ca").toStringList();
//    DEFAULTCONFIG::annDefaultConfigPath = QSettingTools::getVariantFromIniFile(path, "sim", "ann").toString();
//    DEFAULTCONFIG::evalDefaultConfigPath = QSettingTools::getVariantFromIniFile(path, "sim", "eval").toString();
    int count = 0;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        QString    str(line);
        str              = str.trimmed();
        QString fileName = MUTILS::getFileNameByPath(str);
        qDebug() << fileName;
        if (fileName != "") {
            if (fileName.startsWith("ca")) {
                DEFAULTCONFIG::caDefaultConfigPath << str;
            } else if (fileName.startsWith("ann")) {
                DEFAULTCONFIG::annDefaultConfigPath = str;
            } else if (fileName.startsWith("eval")) {
                DEFAULTCONFIG::evalDefaultConfigPath = str;
            } else if (fileName == "land.ini") {
                DEFAULTCONFIG::landConfigPath = str;
            } else {
                QMessageBox::critical(nullptr, "TIPS!",
                    QString::fromLocal8Bit("配置文件名以ca_xxx.json、ann_xxx.json、eval_xxx.json, 错误命名：")
                        + path);
                return false;
            }
            count++;
        } else {
            QMessageBox::critical(
                nullptr, "TIPS!", path + "==>" + str + QString::fromLocal8Bit("文件名为空或不存在"));
        }
    }
    if (count < 2) {
        QMessageBox::critical(
            nullptr, "TIPS!", path + QString::fromLocal8Bit("配置文件没有合法内容！！！"));
        return false;
    }
    qDebug() << DEFAULTCONFIG::caDefaultConfigPath;
    qDebug() << DEFAULTCONFIG::annDefaultConfigPath;
    qDebug() << DEFAULTCONFIG::evalDefaultConfigPath;
    bool res = DEFAULTCONFIG::loadTifPathFromJson();
    return res;
}

QStringList getYearsOfCA() {
    qDebug() << "***" << caDefaultConfigPath;
    QStringList res;
    for (QString tmp : caDefaultConfigPath) {
        QString year = MUTILS::getFileNameByPath(tmp).split("_")[1].split(".")[0];
        res << year;
        insertKeyValueSafe(year, tmp);
    }
    return res;
}

}  // namespace DEFAULTCONFIG
