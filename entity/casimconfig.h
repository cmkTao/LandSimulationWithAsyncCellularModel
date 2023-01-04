#ifndef CASIMCONFIG_H
#define CASIMCONFIG_H
#include <QList>
#include <QString>

class CaSimConfig {
public:
    CaSimConfig();

private:
    QString        caMode;
    QList<QString> colorsHexStr;
};

#endif  // CASIMCONFIG_H
