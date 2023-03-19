#include "Board.hpp"
#include "Type.hpp"
#include "Util.hpp"
#include <ag/agOne.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
#include <ag/scene/SceneBase.hpp>
#include <ag/scene/SceneManager.hpp>
#include <ag/util/Random.hpp>
#include <algorithm>
#include <cassert>
#include <vector>

const glm::ivec2 k_windowSize = { 480, 640 };

class TitleScene : public ag::SceneBase {
public:
    void show() override
    {
        m_isFinished = false;
        m_nextScene = "Game";
    }
    void update(const ag::InputState& input, float deltaTime) override
    {
        if (input.getKeyboardState().getKeyState(ag::KeyCode::enter) == ag::ButtonState::Pressed) {
            m_isFinished = true;
        }
    }
    void draw(const ag::Renderer::Instance& renderer) override
    {
        {
            glm::ivec2 size = renderer->measureString(32, u"Tetris");
            renderer->drawString((k_windowSize - size) / 2, 32, u"Tetris", glm::vec4(1, 1, 1, 1));
        }
        {
            glm::ivec2 size = renderer->measureString(32, u"Enterでスタート");
            glm::ivec2 center = (k_windowSize - size) / 2;
            center.y = 400;
            renderer->drawString(center, 32, u"Enterでスタート", glm::vec4(1, 1, 1, 1));
        }
    }
    void hide() override
    {
    }

private:
};

class GameScene : public ag::SceneBase {
public:
    void show() override
    {
        m_board.clear();
        initFall();
        m_gameEnd = false;
    }

    void update(const ag::InputState& input, float deltaTime) override
    {
        if (m_gameEnd) {
            if (input.getKeyboardState().getKeyState(ag::KeyCode::enter) == ag::ButtonState::Pressed) {
                show();
            }
            return;
        }
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
        if (m_board.isIntersects(m_currentPos.y, m_currentPos.x, m_current)) {
            m_currentPos = savePos;
            m_current = saveTable;
        }
        // fall piece.
        m_time += ag::Engine::getInstance()->getLooper()->deltaTime();
        if (m_time >= 0.2f) {
            m_currentPos.y += 1;
            m_time = 0.0f;
        }
        if (m_board.isGround(m_currentPos.y, m_currentPos.x, m_current)) {
            m_board.put(m_currentPos.y, m_currentPos.x, m_current);
            m_board.match();
            initFall();
        }
    }

    void draw(const ag::Renderer::Instance& renderer) override
    {
        // draw game
        for (int i = 0; i < Board::k_rowMax; i++) {
            for (int j = 0; j < Board::k_columnMax; j++) {
                drawPiece(renderer, i, j, m_board.get(i, j));
            }
        }
        if (!m_current.empty()) {
            drawPiece(renderer, m_currentPos.y, m_currentPos.x, m_current);
        }
        for (int i = 0; i < Board::k_rowMax; i++) {
            for (int j = 0; j < Board::k_columnMax; j++) {
                glm::vec2 pos = glm::vec2(1 + (j * 32), (i * 32));
                glm::vec2 size = glm::vec2(32, 32);
                renderer->drawRect(pos, size, glm::vec4(1, 1, 1, 1));
            }
        }
        drawPiece(renderer, 2, Board::k_columnMax + 1, m_next);
        // draw result
        if (m_gameEnd) {
            renderer->fillRect(glm::vec2(), k_windowSize, glm::vec4(1, 1, 1, 0.5f));
            {
                glm::ivec2 size = renderer->measureString(32, u"Enterでもう一度");
                renderer->drawString((k_windowSize - size) / 2, 32, u"Enterでもう一度", glm::vec4(0, 0, 0, 1));
            }
        }
    }

    void hide() override
    {
    }

private:
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

    void initFall()
    {
        if (m_next.empty()) {
            m_current = k_pieceTables.at(ag::Random::range(0, k_pieceTables.size() - 1));
        } else {
            m_current = m_next;
        }
        m_currentPos = glm::vec2(ag::Random::range(0, Board::k_columnMax - util::getPieceWidth(m_current)), 0);
        m_next = k_pieceTables.at(ag::Random::range(0, k_pieceTables.size() - 1));
        m_time = 0.0f;
    }

    PieceTable rotatePiece(const PieceTable& t)
    {
        PieceTable a;
        int rc = util::getPieceHeight(t);
        int cc = util::getPieceWidth(t);
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

    Board m_board;
    PieceTable m_next;
    PieceTable m_current;
    glm::vec2 m_currentPos;
    float m_time;
    bool m_gameEnd;
};

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
        , m_sceneManager({
              { "Title", std::make_shared<TitleScene>() },
              { "Game", std::make_shared<GameScene>() },
          })
    {
    }
    void start(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        renderer->setFontMap(loadFontMap("testdata/fonts/NotoSansJP-Medium.otf"));
        m_sceneManager.start("Title");
    }

    void update(const ag::Window::Instance& window, const ag::InputState& input, const ag::Renderer::Instance& renderer)
    {
        renderer->begin(window, ag::RenderPass::default2D());
        m_sceneManager.update(input, ag::Engine::getInstance()->getLooper()->deltaTime());
        m_sceneManager.draw(renderer);
        renderer->end();
    }

private:
    ag::SceneManager m_sceneManager;
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(k_windowSize.x, k_windowSize.y, false, "Tetris");
}