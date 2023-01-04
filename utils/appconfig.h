#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QString>
class AppConfig
{
public:
    AppConfig();
    static bool autoLoadConfig;
    static bool useAbsoluePath;
    static QString dataDir;
    static QString simConfigDir;
};

#endif // APPCONFIG_H
