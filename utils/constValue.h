#ifndef CONSTVALUE_H
#define CONSTVALUE_H
#include <QString>
namespace CVALUE {

// 异步CA的三种模式
enum class MODE
{
    B,
    L,
    U
};

// 采样模式
enum class SAMPMODE
{
    U,
    R
};

//  输入概率模式（ANN）
enum class PROBMODE
{
    FIXED,            // 固定概率值1
    RANDOMLAYERSAME,  // 随机设置概率值，所有层同一个随机值
    RANDOM            //  不同层不同随机值
};

struct BatchRunStatus {
    QString finished = "finished";
    QString waiting  = "waiting";
    QString running  = "running";
};

const int  MAX_LAND_TYPE    = 20;

#ifdef QT_NO_DEBUG
    const QString appConfigFilePath = "F:\\code\\app.ini";
#else
    const QString appConfigFilePath = "./app.ini";
#endif
}  // namespace CVALUE
#endif  // CONSTVALUE_H
