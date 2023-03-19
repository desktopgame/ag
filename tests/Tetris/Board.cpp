#include "Board.hpp"
#include "Util.hpp"

Board::Board()
    : m_table()
{
}

void Board::put(int row, int column, const PieceTable& t)
{
    for (int i = 0; i < util::getPieceHeight(t); i++) {
        for (int j = 0; j < util::getPieceWidth(t); j++) {
            PieceColor pc = t[i][j];
            if (pc == PieceColor::None) {
                continue;
            }
            m_table.at(row + i).at(column + j) = pc;
        }
    }
    /*
    // judge
    auto firstLine = m_table.at(0);
    for (PieceColor pc : firstLine) {
        if (pc != PieceColor::None) {
            m_gameEnd = true;
        }
    }
    */
}
PieceColor Board::get(int row, int column) const
{
    return m_table.at(row).at(column);
}
bool Board::isGround(int row, int column, const PieceTable& t)
{
    for (int i = 0; i < util::getPieceHeight(t); i++) {
        for (int j = 0; j < util::getPieceWidth(t); j++) {
            if (t[i][j] == PieceColor::None) {
                continue;
            }
            int tr = row + i + 1;
            int tc = column + j;
            if (tr >= k_rowMax) {
                return true;
            }
            if (m_table[tr][tc] != PieceColor::None) {
                return true;
            }
        }
    }
    return false;
}
bool Board::isIntersects(int row, int column, const PieceTable& t)
{
    for (int i = 0; i < util::getPieceHeight(t); i++) {
        for (int j = 0; j < util::getPieceWidth(t); j++) {
            int tr = row + i;
            int tc = column + j;
            if (tr < 0 || tr >= k_rowMax || tc < 0 || tc >= k_columnMax) {
                return true;
            }
            if (m_table[tr][tc] != PieceColor::None) {
                return true;
            }
        }
    }
    return false;
}
void Board::match()
{
    for (int i = 0; i < k_rowMax; i++) {
        auto& line = m_table.at(i);
        if (std::find(line.begin(), line.end(), PieceColor::None) != line.end()) {
            continue;
        }
        for (int j = i; j >= 1; j--) {
            auto& src = m_table.at(j - 1);
            auto& dst = m_table.at(j);
            for (int k = 0; k < k_columnMax; k++) {
                dst.at(k) = src.at(k);
                src.at(k) = PieceColor::None;
            }
        }
    }
}
void Board::clear()
{
    m_table = {};
    for (int i = 0; i < k_rowMax; i++) {
        PieceLine line;
        for (int j = 0; j < k_columnMax; j++) {
            line.push_back(PieceColor::None);
        }
        m_table.push_back(line);
    }
}