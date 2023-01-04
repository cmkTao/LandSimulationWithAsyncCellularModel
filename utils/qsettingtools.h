#ifndef QSETTINGTOOLS_H
#define QSETTINGTOOLS_H

#include <QColor>
#include <QMap>
#include <QSettings>
#include <QTextCodec>

#include "utils/mutils.h"
/**
 * @brief The QSettingTools class
 *  操作QSetting的自定义工具类
 */
class QSettingTools {
public:
    QSettingTools();

    // ======================== 土地颜色和名称配置的保存与读取 ==============================
    /**
     * @brief saveLandColorsNames 保存土地类型对应的 颜色 和 名称到ini文件
     * @param filePath 配置文件路径
     * @param colorMap code-颜色map 1开始编号
     * @param nameMap code-名称map 1开始编号
     */
    static void saveLandColorsNames(QString filePath, QMap<double, QColor> colorMap, QMap<double, QString> nameMap);

    /**
     * @brief getLandColorsNames 读取土地类型对应的 颜色 和 名称到ini文件
     * @param filePath 配置文件路径
     * @param colorMap code-颜色map 1开始编号
     * @param nameMap code-名称map 1开始编号
     */
    static void getLandColorsNames(QString filePath, QMap<double, QColor> &colorMap, QMap<double, QString> &nameMap);
    // ======================== 土地颜色和名称配置的保存与读取 ==============================

    static QString getStringValueFromIniFile(QString filePath, QString groupName, QString key);

    static QVariant getVariantFromIniFile(QString filePath, QString groupName, QString key);
};

#endif  // QSETTINGTOOLS_H
