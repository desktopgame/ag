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
        m_fall.save();
        if (input.getKeyboardState().getKeyState(ag::KeyCode::left) == ag::ButtonState::Pressed) {
            m_fall.move({ -1, 0 });
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::right) == ag::ButtonState::Pressed) {
            m_fall.move({ 1, 0 });
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::down) == ag::ButtonState::Pressed) {
            m_fall.move({ 0, 1 });
        } else if (input.getKeyboardState().getKeyState(ag::KeyCode::space) == ag::ButtonState::Pressed) {
            m_fall.rotate();
        }
        if (m_board.isIntersects(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent())) {
            m_fall.restore();
        }
        // fall piece.
        if (m_board.isGround(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent())) {
            m_board.put(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent());
            m_board.match();
            m_fall.reset();
            return;
        }
        m_fall.tick(ag::Engine::getInstance()->getLooper()->deltaTime());
        if (m_board.isGround(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent())) {
            m_board.put(m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent());
            m_board.match();
            m_fall.reset();
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
        drawPiece(renderer, m_fall.getRow(), m_fall.getColumn(), m_fall.getCurrent());
        for (int i = 0; i < Board::k_rowMax; i++) {
            for (int j = 0; j < Board::k_columnMax; j++) {
                glm::vec2 pos = glm::vec2(1 + (j * 32), (i * 32));
                glm::vec2 size = glm::vec2(32, 32);
                renderer->drawRect(pos, size, glm::vec4(1, 1, 1, 1));
            }
        }
        drawPiece(renderer, 2, Board::k_columnMax + 1, m_fall.getNext());
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

    Board m_board;
    Fall m_fall;
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