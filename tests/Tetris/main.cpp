#include "Board.hpp"
#include "Fall.hpp"
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
        m_fall.reset();
        m_score = 0;
        m_gameEnd = false;
    }

    void update(const ag::InputState& input, float deltaTime) override
    {
        const ag::KeyboardState& kb = input.getKeyboardState();
        if (m_gameEnd) {
            if (kb.getKeyState(ag::KeyCode::enter) == ag::ButtonState::Pressed) {
                show();
            }
            return;
        }
        // input control for piece.
        m_fall.save();
        if (kb.getKeyState(ag::KeyCode::left) == ag::ButtonState::Pressed) {
            m_fall.move({ -1, 0 });
        } else if (kb.getKeyState(ag::KeyCode::right) == ag::ButtonState::Pressed) {
            m_fall.move({ 1, 0 });
        } else if (kb.getKeyState(ag::KeyCode::down) == ag::ButtonState::Pressed) {
            m_fall.move({ 0, 1 });
        } else if (kb.getKeyState(ag::KeyCode::enter) == ag::ButtonState::Pressed || input.getKeyboardState().getKeyState(ag::KeyCode::kpEnter) == ag::ButtonState::Pressed) {
            m_fall.locate({ m_fall.getColumn(), m_board.calcGroundRow(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent()) });
        } else if (kb.getKeyState(ag::KeyCode::space) == ag::ButtonState::Pressed) {
            m_fall.rotate();
        }
        if (m_board.isIntersects(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent())) {
            m_fall.restore();
        }
        // fall piece.
        if (m_board.isGround(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent())) {
            m_board.put(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent());
            m_score += m_board.match() * 10;
            m_fall.reset();
            return;
        }
        m_fall.tick(ag::Engine::getInstance()->getLooper()->deltaTime());
        if (m_board.isGround(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent())) {
            m_board.put(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent());
            m_score += m_board.match() * 10;
            m_fall.reset();
        }
    }

    void draw(const ag::Renderer::Instance& renderer) override
    {
        // draw static pieces
        for (int i = 0; i < Board::k_rowMax; i++) {
            for (int j = 0; j < Board::k_columnMax; j++) {
                drawPiece(renderer, i, j, m_board.get(i, j), false);
            }
        }
        // draw ghost
        int ghostRow = m_board.calcGroundRow(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent());
        drawPiece(renderer, ghostRow, m_fall.getColumn(), m_fall.getCurrent(), true);
        // draw falling piece
        drawPiece(renderer, m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent(), false);
        // draw grid
        for (int i = 0; i < Board::k_rowMax; i++) {
            for (int j = 0; j < Board::k_columnMax; j++) {
                glm::vec2 pos = glm::vec2(1 + (j * 32), (i * 32));
                glm::vec2 size = glm::vec2(32, 32);
                renderer->drawRect(pos, size, glm::vec4(1, 1, 1, 1));
            }
        }
        // draw next piece
        drawPiece(renderer, 2, Board::k_columnMax + 1, m_fall.getNext(), false);
        // draw score
        char scoreChars[9] = {};
        memset(scoreChars, '\0', sizeof(scoreChars));
        ::sprintf(scoreChars, "%08d", m_score);
        std::vector<char16_t> scoreVec;
        for (char c : scoreChars) {
            if (c == '\0')
                break;
            scoreVec.push_back(static_cast<char16_t>(c));
        }
        std::u16string scoreString = std::u16string(scoreVec.begin(), scoreVec.end());
        glm::vec2 scoreSize = renderer->measureString(32, scoreString);
        int space = k_windowSize.x - (32 * 10);
        renderer->drawString(glm::vec2(32 * 10) + (space - scoreSize.x) / 2, 32, scoreString, glm::vec4(1, 1, 1, 1));
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
    void drawPiece(const std::shared_ptr<ag::Renderer>& r, int row, int column, const PieceTable& table, bool isGhost)
    {
        for (int i = 0; i < table.size(); i++) {
            for (int j = 0; j < table.at(i).size(); j++) {
                PieceColor pc = table.at(i).at(j);
                drawPiece(r, row + i, column + j, pc, isGhost);
            }
        }
    }

    void drawPiece(const std::shared_ptr<ag::Renderer>& r, int row, int column, PieceColor pc, bool isGhost)
    {
        if (pc == PieceColor::None) {
            return;
        }
        glm::vec2 pos = glm::vec2(1 + (column * 32), row * 32);
        glm::vec4 color;
        glm::vec4 mult = isGhost ? glm::vec4(0.5f, 0.5f, 0.5f, 1) : glm::vec4(1, 1, 1, 1);
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
        r->fillRect(pos, glm::vec2(32, 32), color * mult);
    }

    Board m_board;
    Fall m_fall;
    int m_score;
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