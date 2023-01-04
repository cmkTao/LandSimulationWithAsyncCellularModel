#ifndef ACCA_V2_H
#define ACCA_V2_H
#include "alglib/ca_v2.h"
#include "utils/constValue.h"

class ACCA_V2 : public CA_V2 {
public:
    ACCA_V2();
    ACCA_V2(QObject *parent, QString filePath, bool needSleep = true);

    // CA interface
public:
    double *calNeighborsProportion(LandCell *cell) override;
    void    startSimulation() override;
    void    setRandMode();
    /**
     * @brief setRandModeWithModeUsed
     * 只更新模式已经被用过的
     */
    void setRandModeWithModeUsed();

    void setNeedSleep(bool needSleep);

protected:
    void initBufferAndMode();
    /**
     * @brief updateBuffer
     * 使用上一轮的状态更新细胞buffer
     * @param cell
     */
    void          updateBuffer(LandCell *cell);
    char **       m_buffer;
    CVALUE::MODE *m_modes;
    QList<int>    m_indexListOfModeUsed;  // 记录mode被用过的元胞下标
    bool          m_needSleep;
};

#endif  // ACCA_V2_H
