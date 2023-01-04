#ifndef CELLSPACE_H
#define CELLSPACE_H

/**
 * @brief The CellSpace class
 * 用于构建细胞空间，使用细胞对象导致占用内存大，用于内存优化
 */
class CellSpace {
public:
    CellSpace();

public:
    int m_row;  // 行数
    int m_col;  // 列数
private:
    char *  m_modeSpace;    // 细胞模式
    char ** m_bufferSpace;  // 细胞的buffer
    double *m_probsData;    // 适应性概率
};

#endif  // CELLSPACE_H
