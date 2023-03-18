#include <ag/agOne.hpp>
#include <ag/easy/App.hpp>
#include <ag/graphics/Model.hpp>
#include <ag/native/glm.hpp>
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

class MyApp : public ag::easy::App {
public:
    MyApp(int argc, char* argv[])
        : App(argc, argv)
    {
    }
    void start(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
    }

    void update(const std::shared_ptr<ag::Window>& w, const std::shared_ptr<ag::Renderer>& r)
    {
        r->begin(w, ag::RenderPass::default2D());
        drawPiece(r, 0, 0, PieceColor::Cyan);
        drawPiece(r, 1, 0, PieceColor::Yellow);
        drawPiece(r, 2, 0, PieceColor::Green);
        drawPiece(r, 3, 0, PieceColor::Red);
        drawPiece(r, 4, 0, PieceColor::Blue);
        drawPiece(r, 5, 0, PieceColor::Orange);
        drawPiece(r, 6, 0, PieceColor::Purple);
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                glm::vec2 pos = glm::vec2(1 + (j * 32), (i * 32));
                glm::vec2 size = glm::vec2(32, 32);
                r->drawRect(pos, size, glm::vec4(1, 1, 1, 1));
            }
        }
        r->end();
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

private:
};

int main(int argc, char* argv[])
{
    MyApp app(argc, argv);
    return app.main(480, 640, false, "Tetris");
}