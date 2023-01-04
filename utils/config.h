#pragma once
#ifndef CONFIG_H
#define CONFIG_H
#include <thirdPart/json/json.h>

#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <fstream>
#include <iostream>

#include "utils/mutils.h"
#include "utils/qsettingtools.h"
namespace DEFAULTCONFIG {

extern bool useOfficalFlusVersion;

extern QString DEFAULT_CONFIG;

const QString DEFAULT_NAME_CONFIG1 = "defaultConfig1.ini";
const QString DEFAULT_NAME_CONFIG2 = "defaultConfig2.ini";
#ifdef QT_NO_DEBUG
const QString DEFAULT_CONFIG1 = "./defaultConfig1.ini";
const QString DEFAULT_CONFIG2 = "./defaultConfig2.ini";
#else
const QString DEFAULT_CONFIG1 = "E:\\project\\c\\qt_project\\defaultConfig\\defaultConfig1.ini";
const QString DEFAULT_CONFIG2 = "E:\\project\\c\\qt_project\\defaultConfig\\defaultConfig2.ini";
#endif
extern QString                annDefaultConfigPath;
extern QStringList            caDefaultConfigPath;
extern QString                evalDefaultConfigPath;
extern QString                landConfigPath;
extern bool                   useOneYear;
extern QMap<QString, QString> namePathMap;
struct TifPathConfig {
    QString     startTifPath;
    QString     endTifPath;
    QStringList simTifPath;
    QString     probsTifPath;
    QStringList getNoEmptyPathList();
    QStringList getDiffPair();  // 获取对比组合
    QString     getFileNameFromPath(QString path);
};
extern TifPathConfig tifPathConfig;
bool                 loadTifPathFromJson();
void                 setDefaultConfigPath();
bool                 loadDefaultConfigPath(QString path="");
void                 insertKeyValueSafe(QString key, QString value);
QStringList          getYearsOfCA();
}  // namespace DEFAULTCONFIG

#endif  // CONFIG_H
