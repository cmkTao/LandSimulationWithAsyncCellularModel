#ifndef CA_V2_H
#define CA_V2_H
#include <alglib/ca.h>
#include <entity/cellspace.h>

class CA_V2 : public CA {
public:
    CA_V2();
    CA_V2(QObject *parent, QString filePath);

protected:
    void startSimulation() override;
    void initCells() override;

    int  char2Int(char c);
    char int2Char(int i);

protected:
    ::CellSpace *m_cellSpace;
    float        m_alpha;

    // CA interface
public:
    int rouletteNewType(LandCell *cell, double landInertia) override;
    /**
     * @brief calNeighborsProportion
     * 获取上一轮邻居的比例
     * @param cell
     * @return
     */
    double *   calNeighborsProportion(LandCell *cell) override;
    QList<int> m_indexList;
    int        m_count;
};

#endif  // CA_V2_H
