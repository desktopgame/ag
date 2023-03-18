#include <ag/agOne.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <ag/util/Random.hpp>
#include <algorithm>
#include <cassert>
#include <vector>

enum class PieceColor {
    None = 0,
    Cyan,
    Yellow,
    Green,
    Red,
    Blue,
    Orange,
    Purple
};

using PieceLine = std::vector<PieceColor>;
using PieceTable = std::vector<PieceLine>;

const std::vector<PieceTable> k_pieceTables = {
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

const int k_rowMax = 20;
const int k_columnMax = 10;

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
        , m_table()
        , m_current()
        , m_currentPos()
        , m_time(0.0f)
    {
    }
    void start(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        for (int i = 0; i < k_rowMax; i++) {
            PieceLine line;
            for (int j = 0; j < k_columnMax; j++) {
                line.push_back(PieceColor::None);
            }
            m_table.push_back(line);
        }
        initFall();
    }

    void update(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        glm::vec2 savePos = m_currentPos;
        PieceTable saveTable = m_current;
        if (input.getKeyboardState().getKeyState(ag::KeyCode::left) == ag::ButtonState::Pressed) {
            m_currentPos.x--;
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::right) == ag::ButtonState::Pressed) {
            m_currentPos.x++;
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::space) == ag::ButtonState::Pressed) {
            m_current = rotatePiece(m_current);
        }
        if (isIntersects(m_currentPos.y, m_currentPos.x, m_current)) {
            m_currentPos = savePos;
            m_current = saveTable;
        }
        m_time += ag::Engine::getInstance()->getLooper()->deltaTime();
        if (m_time >= 0.2f) {
            m_currentPos.y += 1;
            m_time = 0.0f;
        }
        if (isGround(m_currentPos.y, m_currentPos.x, m_current)) {
            putPiece(m_currentPos.y, m_currentPos.x, m_current);
            deleteLine();
            initFall();
        }
        drawGame(window, renderer);
    }

private:
    // draw

    void drawGame(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        r->begin(w, ag::RenderPass::default2D());
        for (int i = 0; i < k_rowMax; i++) {
            for (int j = 0; j < k_columnMax; j++) {
                drawPiece(r, i, j, m_table.at(i).at(j));
            }
        }
        if (!m_current.empty()) {
            drawPiece(r, m_currentPos.y, m_currentPos.x, m_current);
        }
        for (int i = 0; i < k_rowMax; i++) {
            for (int j = 0; j < k_columnMax; j++) {
                glm::vec2 pos = glm::vec2(1 + (j * 32), (i * 32));
                glm::vec2 size = glm::vec2(32, 32);
                r->drawRect(pos, size, glm::vec4(1, 1, 1, 1));
            }
        }
        r->end();
    }

    void drawPiece(const std::shared_ptr<ag::Renderer>& r, int row, int column, const PieceTable& table)
    {
        for (int i = 0; i < table.size(); i++) {
            for (int j = 0; j < table.at(i).size(); j++) {
                PieceColor pc = table.at(i).at(j);
                drawPiece(r, row + i, column + j, pc);
            }
        }
    }

    void drawPiece(const std::shared_ptr<ag::Renderer>& r, int row, int column, PieceColor pc)
    {
        if (pc == PieceColor::None) {
            return;
        }
        glm::vec2 pos = glm::vec2(1 + (column * 32), row * 32);
        glm::vec4 color;
        switch (pc) {
        case PieceColor::None:
            break;
        case PieceColor::Cyan:
            color = glm::vec4(0.2f, 0.8f, 0.8f, 1);
            break;
        case PieceColor::Yellow:
            color = glm::vec4(1, 1, 0, 1);
            break;
        case PieceColor::Green:
            color = glm::vec4(0, 1, 0, 1);
            break;
        case PieceColor::Red:
            color = glm::vec4(1, 0, 0, 1);
            break;
        case PieceColor::Blue:
            color = glm::vec4(0, 0, 1, 1);
            break;
        case PieceColor::Orange:
            color = glm::vec4(1, 0.5f, 0, 1);
            break;
        case PieceColor::Purple:
            color = glm::vec4(1, 0, 1, 1);
            break;
        }
        r->fillRect(pos, glm::vec2(32, 32), color);
    }

    // utility

    void initFall()
    {
        m_current = k_pieceTables.at(ag::Random::range(0, k_pieceTables.size() - 1));
        m_currentPos = glm::vec2(ag::Random::range(0, k_columnMax - getPieceWidth(m_current)), 0);
    }

    PieceTable rotatePiece(const PieceTable& t)
    {
        PieceTable a;
        int rc = getPieceHeight(t);
        int cc = getPieceWidth(t);
        for (int i = 0; i < cc; i++) {
            PieceLine line;
            for (int j = 0; j < rc; j++) {
                line.emplace_back(PieceColor::None);
            }
            a.emplace_back(line);
        }
        for (int i = 0; i < rc; i++) {
            for (int j = 0; j < cc; j++) {
                a[j][rc - i - 1] = t[i][j];
            }
        }
        return a;
    }

    void putPiece(int row, int column, const PieceTable& t)
    {
        for (int i = 0; i < getPieceHeight(t); i++) {
            for (int j = 0; j < getPieceWidth(t); j++) {
                PieceColor pc = t[i][j];
                if (pc == PieceColor::None) {
                    continue;
                }
                m_table.at(row + i).at(column + j) = pc;
            }
        }
    }

    void deleteLine()
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

    bool isGround(int row, int column, const PieceTable& t)
    {
        for (int i = 0; i < getPieceHeight(t); i++) {
            for (int j = 0; j < getPieceWidth(t); j++) {
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

    bool isIntersects(int row, int column, const PieceTable& t)
    {
        for (int i = 0; i < getPieceHeight(t); i++) {
            for (int j = 0; j < getPieceWidth(t); j++) {
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

    int getPieceWidth(const PieceTable& t) { return t.at(0).size(); }

    int getPieceHeight(const PieceTable& t) { return t.size(); }

    PieceTable m_table;
    PieceTable m_current;
    glm::vec2 m_currentPos;
    float m_time;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(480, 640, false, "Tetris");
}