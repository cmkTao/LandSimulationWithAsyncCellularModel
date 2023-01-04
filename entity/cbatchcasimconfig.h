#ifndef CBATCHCASIMCONFIG_H
#define CBATCHCASIMCONFIG_H
#include <entity/global_entity.h>
#include <thirdPart/json/json.h>
#include <utils/mutils.h>

#include <QDebug>
#include <QDir>
#include <QList>
#include <QString>
#include <fstream>
#include <iostream>
using namespace std;
class CBatchCaSimConfig {
public:
    CBatchCaSimConfig();
    CBatchCaSimConfig(QString curDir, int epoches);

    void print();

    /**
     * @brief setSimSavePath2Config 更新配置文件中模拟结果保存路径
     * @param configPath 配置文件路径
     * @param simSavePath 新的模拟文件保存路径
     */
    void setSimSavePath2Config(QString configPath, QString simSavePath);

    /**
     * @brief setSimSavePath2Config 设置某一轮的保存路径
     * @param configPath
     * @param epoch 从1开始
     */
    void setSimSavePath2Config(QString configPath, int epoch);
    void setSimSavePath2Config(int epoch);
    /**
     * @brief getSimSavePathFromConfig 获取配置文件中模拟结果保存路径
     * @param configPath 配置文件路径
     * @return
     */

    QString getSimSavePathFromConfig(QString configPath, QString key = "saveSimPath");
    QString getValueFromJsonByKey(QString configPath, QString key = "saveSimPath");
    void    setValueToJsonByKey(QString key, QString value);
    void    setValueToJsonByKey(QString configPath, QString key, QString value);
    void    setValueToJsonByKey(QString key, int value);
    void    setValueToJsonByKey(QString key, double value);
    void    setValueToJsonByKey(QString key, QList<QList<double>> value);
    void    setValueToJsonByKey(QString key, QList<double> value);
    void    setValueToJsonByKey(QString key, QList<int> value);
    void    updateToJsonFile();

    /**
     * @brief saveToOther 另存为
     * @param filePath
     */
    void saveToOther(QString filePath);

    void saveConfigToOther(QString configPath, QString otherPath);

    /**
     * @brief saveEvalToOther 将验证配置文件另存为
     * @param filePath
     */
    void saveEvalToOther(QString filePath);

    int getMaxIterNumFromConfig(QString configPath);

    /**
     * @brief resetSimPath2Config 重置模拟结果保存路径
     */
    void resetSimPath2Config();

    bool isValid() const;

    QList<QString> getSimSavePathOfEachEpochList();

    QString getCaConfigPath() const;

    int getEpoches() const;

    QString getCaMode() const;

    int getIterTimes() const;

    QString getCurDir() const;

    QString getEvalConfigPath() const;
    /**
     * @brief genEvalConfig 传入目标真实tif路径生成新的计算评价指标的配置文件
     * @param endTifPath
     * @return
     */
    QString genEvalConfig(QString endTifPath);

    /* 公有属性 */
    SValRes m_meanValRes;  // 记录该配置多次运行的平均结果

    /**
     * @brief getCurConfigName 获取当前配置的名称，为当前配置所在目录名称
     * @return
     */
    QString getCurConfigDirName();

    int  getEndIterTimes() const;
    void setEndIterTimes(int endIterTimes);
    int  getMeanIterTimes();

    void setMeanEndIterTimes(int meanEndIterTimes);

    int getMeanEndIterTimes() const;

    QList<int> getLandUseDemand() const;
    void       setLandUseDemand(const QList<int> &landUseDemand);

    QList<QList<double>> getCostMatrix() const;
    void                 setCostMatrix(const QList<QList<double>> &costMatrix);

    QList<double> getWnb() const;
    void          setWnb(const QList<double> &wnb);

    int  getMaxIter() const;
    void setMaxIter(int maxIter);

    int  getEndDiffValue() const;
    void setEndDiffValue(int endDiffValue);

    int  getNeiOdd() const;
    void setNeiOdd(int neiOdd);

    double getCaRatio() const;
    void   setCaRatio(double caRatio);

    QString getCurName() const;

private:
    void initFromJsonFile();

    /*                    属性                      */
    QString        m_curDir;             // 当前配置文件所在目录
    QString        m_curName;            // 当前配置所在目录名称
    bool           m_isValidConfig;      // 是否是一个合法的配置（ca*.json格式命名的配置文件）
    QString        m_caConfigPath;       // ca模拟配置文件路径
    QString        m_simSaveNamePrefix;  // ca模拟结果名称前缀
    QString        m_simSavePath;        // ca模拟结果保存路径
    QString        m_evalConfigPath;     // 用于验证的配置文件
    int            m_iterTimes;          // 迭代次数
    int            m_endIterTimes;       // 终止时迭代次数
    int            m_meanEndIterTimes;   // 平均迭代次数
    int            m_epoches;            // 该配置文件重复模拟的次数
    QList<QString> m_simSavePathOfEachEpochList;  //   同一配置多次运行，每次结果保存位置
    QString        m_caMode;                      //  ca模式(ACA、CA)

    QList<int>           m_landUseDemand;
    QList<QList<double>> m_costMatrix;
    QList<double>        m_wnb;      // 邻域权重
    int                  m_maxIter;  // 最大迭代次数
    int                  m_endDiffValue;
    int                  m_neiOdd;  // 邻域大小
    double               m_acaRatio;
};

#endif  // CBATCHCASIMCONFIG_H
