#pragma once
#include "Type.hpp"
#include <ag/native/glm.hpp>

class Fall {
public:
    explicit Fall();

    void reset();
    void tick(float deltaTime);

    void save();
    void move(const glm::ivec2 offs);
    void locate(const glm::ivec2 pos);
    void rotate();
    void restore();

    const PieceTable& getCurrent() const;
    const PieceTable& getNext() const;
    int getRow() const;
    int getColumn() const;
    glm::ivec2 getPosition() const;

private:
    static const inline std::vector<PieceTable> k_pieceTables = {
        // I
        { { PieceColor::Cyan, PieceColor::Cyan, PieceColor::Cyan, PieceColor::Cyan } },
        // O
        {
            { PieceColor::Yellow, PieceColor::Yellow },
            { PieceColor::Yellow, PieceColor::Yellow },
        },
        // S
        {
            { PieceColor::None, PieceColor::Green, PieceColor::Green },
            { PieceColor::Green, PieceColor::Green, PieceColor::None },
        },
        // Z
        {
            { PieceColor::Red, PieceColor::Red, PieceColor::None },
            { PieceColor::None, PieceColor::Red, PieceColor::Red },
        },
        // L
        {
            { PieceColor::Orange, PieceColor::None, PieceColor::None },
            { PieceColor::Orange, PieceColor::Orange, PieceColor::Orange },
        },
        // T
        {
            { PieceColor::None, PieceColor::Purple, PieceColor::None },
            { PieceColor::Purple, PieceColor::Purple, PieceColor::Purple },
        }
    };

    PieceTable m_next;
    PieceTable m_current;
    glm::ivec2 m_position;
    float m_time;

    PieceTable m_saveTable;
    glm::ivec2 m_savePosition;
};