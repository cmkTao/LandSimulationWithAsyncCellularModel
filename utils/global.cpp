#include "global.h"

Global::Global() {}
bool Global::useOfficialFlus    = true;   // 使用官方版本
bool Global::useV2              = true;   // 使用细胞版本/数组版本V2
bool Global::useProbCheck       = false;  // 使用概率检查
bool Global::changeAlphaSetMode = true;   // 只更新alpha子集中细胞的模式
