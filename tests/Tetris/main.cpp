#include <ag/agOne.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <ag/util/Random.hpp>
#include <algorithm>
#include <cassert>
#include <vector>

enum class GameState {
    Title,
    Game,
    Result
};

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
const glm::ivec2 k_windowSize = { 480, 640 };

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
        , m_table()
        , m_next()
        , m_current()
        , m_currentPos()
        , m_time(0.0f)
        , m_state(GameState::Title)
    {
    }
    void start(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        renderer->setFontMap(loadFontMap("testdata/fonts/NotoSansJP-Medium.otf"));
    }

    void update(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        renderer->begin(window, ag::RenderPass::default2D());
        switch (m_state) {
        case GameState::Title:
            updateTitle(window, input, renderer);
            drawTitle(window, renderer);
            break;
        case GameState::Game:
            updateGame(window, input, renderer);
            drawGame(window, renderer);
            break;
        case GameState::Result:
            updateResult(window, input, renderer);
            drawResult(window, renderer);
            break;
        }
        renderer->end();
    }

private:
    // title

    void updateTitle(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        if (input.getKeyboardState().getKeyState(ag::KeyCode::enter) == ag::ButtonState::Pressed) {
            m_state = GameState::Game;
            initGame();
            initFall();
        }
    }

    void drawTitle(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        {
            glm::ivec2 size = r->measureString(32, u"Tetris");
            r->drawString((k_windowSize - size) / 2, 32, u"Tetris", glm::vec4(1, 1, 1, 1));
        }
        {
            glm::ivec2 size = r->measureString(32, u"Enterでスタート");
            glm::ivec2 center = (k_windowSize - size) / 2;
            center.y = 400;
            r->drawString(center, 32, u"Enterでスタート", glm::vec4(1, 1, 1, 1));
        }
    }

    // game

    void updateGame(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        // input control for piece.
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
        // fall piece.
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
    }

    void drawGame(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
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
        drawPiece(r, 2, k_columnMax + 1, m_next);
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

    void initGame()
    {
        m_table.clear();
        for (int i = 0; i < k_rowMax; i++) {
            PieceLine line;
            for (int j = 0; j < k_columnMax; j++) {
                line.push_back(PieceColor::None);
            }
            m_table.push_back(line);
        }
    }

    void initFall()
    {
        if (m_next.empty()) {
            m_current = k_pieceTables.at(ag::Random::range(0, k_pieceTables.size() - 1));
        } else {
            m_current = m_next;
        }
        m_currentPos = glm::vec2(ag::Random::range(0, k_columnMax - getPieceWidth(m_current)), 0);
        m_next = k_pieceTables.at(ag::Random::range(0, k_pieceTables.size() - 1));
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
        // judge
        auto firstLine = m_table.at(0);
        for (PieceColor pc : firstLine) {
            if (pc != PieceColor::None) {
                m_state = GameState::Result;
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

    // result

    void updateResult(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        if (input.getKeyboardState().getKeyState(ag::KeyCode::enter) == ag::ButtonState::Pressed) {
            m_state = GameState::Game;
            initGame();
            initFall();
        }
    }

    void drawResult(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        drawGame(w, r);
        r->fillRect(glm::vec2(), k_windowSize, glm::vec4(1, 1, 1, 0.5f));
        {
            glm::ivec2 size = r->measureString(32, u"Enterでもう一度");
            r->drawString((k_windowSize - size) / 2, 32, u"Enterでもう一度", glm::vec4(0, 0, 0, 1));
        }
    }

    PieceTable m_table;
    PieceTable m_next;
    PieceTable m_current;
    glm::vec2 m_currentPos;
    float m_time;
    GameState m_state;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(k_windowSize.x, k_windowSize.y, false, "Tetris");
}