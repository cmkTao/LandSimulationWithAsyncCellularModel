#include "appconfig.h"

AppConfig::AppConfig()
{

}
bool AppConfig::autoLoadConfig    = true;   // 自动配置
bool AppConfig::useAbsoluePath     = true;   // 使用绝对路径
QString AppConfig::dataDir = "F:\\code\\datas";
//QString AppConfig::simConfigDir = "F:\\code\\configs";
QString AppConfig::simConfigDir = "F:\\code\\configs";
