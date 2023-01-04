#ifndef GLOBAL_H
#define GLOBAL_H

class Global {
public:
    Global();
    static bool useOfficialFlus;  // 使用官方版本
    static bool useV2;            // 使用版本2
    static bool useProbCheck;
    static bool changeAlphaSetMode;
};

#endif  // GLOBAL_H
