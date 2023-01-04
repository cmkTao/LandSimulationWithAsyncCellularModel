#include "qsettingtools.h"

QSettingTools::QSettingTools() {}

// ======================== 土地颜色和名称配置的保存与读取 ==============================
/**
 * @brief saveLandColorsNames 保存土地类型对应的 颜色 和 名称到ini文件
 * @param filePath 配置文件路径
 * @param colorMap code-颜色map 0开始编号
 * @param nameMap code-名称map 0开始编号
 */
void QSettingTools::saveLandColorsNames(
    QString filePath, QMap<double, QColor> colorMap, QMap<double, QString> nameMap) {
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup("Colors");
    QMapIterator<double, QColor> ic(colorMap);
    while (ic.hasNext()) {
        ic.next();
        settings.setValue(QString::number(ic.key()), MUTILS::qColor2HexStr(ic.value()));
    }
    settings.endGroup();

    settings.beginGroup("Names");
    QMapIterator<double, QString> nc(nameMap);
    while (nc.hasNext()) {
        nc.next();
        settings.setValue(QString::number(nc.key()), nc.value());
    }
    settings.endGroup();
}

/**
 * @brief getLandColorsNames 读取土地类型对应的 颜色 和 名称到ini文件
 * @param filePath 配置文件路径
 * @param colorMap code-颜色map 1开始编号
 * @param nameMap code-名称map 1开始编号
 */
void QSettingTools::getLandColorsNames(
    QString filePath, QMap<double, QColor> &colorMap, QMap<double, QString> &nameMap) {
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    colorMap.clear();
    nameMap.clear();
    QStringList keys;
    settings.beginGroup("Colors");
    keys = settings.allKeys();
    for (QString key : keys) {
        colorMap[key.toDouble()] = MUTILS::hexStr2QColor(settings.value(key).toString());
    }
    settings.endGroup();

    settings.beginGroup("Names");
    keys = settings.allKeys();
    for (QString key : keys) {
        nameMap[key.toDouble()] = settings.value(key).toString();
    }
    settings.endGroup();
}

QString QSettingTools::getStringValueFromIniFile(QString filePath, QString groupName, QString key)
{
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup(groupName);
    auto v = settings.value(key).toString();
    settings.endGroup();
    qDebug() << QString("filePath[%1] groupName[%2] key[%3]").arg(filePath).arg(groupName).arg(key);
    return v;
}

QVariant QSettingTools::getVariantFromIniFile(QString filePath, QString groupName, QString key)
{
    QSettings settings(filePath, QSettings::IniFormat);
    settings.setIniCodec(QTextCodec::codecForName("GB2312"));
    settings.beginGroup(groupName);
    auto v = settings.value(key);
    settings.endGroup();
    qDebug() << QString("filePath[%1] groupName[%2] key[%3]").arg(filePath).arg(groupName).arg(key);
    return v;
}

// ======================== 土地颜色和名称配置的保存与读取 ==============================
