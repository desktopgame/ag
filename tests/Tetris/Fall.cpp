#include "Fall.hpp"
#include "Board.hpp"
#include "Util.hpp"
#include <ag/util/Random.hpp>

Fall::Fall()
    : m_next()
    , m_current()
    , m_position()
    , m_time()
    , m_saveTable()
    , m_savePosition()
{
}

void Fall::reset()
{
    if (m_next.empty()) {
        m_current = k_pieceTables.at(ag::Random::range(0, k_pieceTables.size() - 1));
    } else {
        m_current = m_next;
    }
    m_position = glm::vec2(ag::Random::range(0, Board::k_columnMax - util::getPieceWidth(m_current)), 0);
    m_next = k_pieceTables.at(ag::Random::range(0, k_pieceTables.size() - 1));
    m_time = 0.0f;
}

void Fall::tick(float deltaTime)
{
    m_time += deltaTime;
    if (m_time >= 0.2f) {
        m_position.y += 1;
        m_time = 0.0f;
    }
}

void Fall::save()
{
    m_saveTable = m_current;
    m_savePosition = m_position;
}
void Fall::move(const glm::ivec2 offs)
{
    m_position += offs;
}
void Fall::rotate()
{
    PieceTable a;
    int rc = util::getPieceHeight(m_current);
    int cc = util::getPieceWidth(m_current);
    for (int i = 0; i < cc; i++) {
        PieceLine line;
        for (int j = 0; j < rc; j++) {
            line.emplace_back(PieceColor::None);
        }
        a.emplace_back(line);
    }
    for (int i = 0; i < rc; i++) {
        for (int j = 0; j < cc; j++) {
            a[j][rc - i - 1] = m_current[i][j];
        }
    }
    m_current = a;
}
void Fall::restore()
{
    m_current = m_saveTable;
    m_position = m_savePosition;
}

const PieceTable& Fall::getCurrent() const { return m_current; }
const PieceTable& Fall::getNext() const { return m_next; }
int Fall::getRow() const { return m_position.y; }
int Fall::getColumn() const { return m_position.x; }
glm::ivec2 Fall::getPosition() const { return m_position; }
