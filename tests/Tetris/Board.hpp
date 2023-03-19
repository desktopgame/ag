#pragma once
#include "Type.hpp"
#include <ag/graphics/Renderer.hpp>

class Board {
public:
    static constexpr inline int k_rowMax = 20;
    static constexpr inline int k_columnMax = 10;
    explicit Board();

    void put(int row, int column, const PieceTable& t);
    PieceColor get(int row, int column) const;
    bool isGround(int row, int column, const PieceTable& t);
    bool isIntersects(int row, int column, const PieceTable& t);
    void match();
    void clear();

private:
    PieceTable m_table;
};