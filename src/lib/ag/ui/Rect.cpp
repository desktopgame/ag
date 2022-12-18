#include <ag/ui/Rect.hpp>

namespace agui {
Rect::Rect()
    : position()
    , size()
{
}

Rect::Rect(const glm::ivec2& position, const glm::ivec2& size)
    : position(position)
    , size(size)
{
}

int Rect::left() const { return position.x; }
int Rect::right() const { return position.x + size.x; }
int Rect::top() const { return position.y; }
int Rect::bottom() const { return position.y + size.y; }
bool Rect::contains(const glm::ivec2& p) const
{
    return p.x >= left() && p.x <= right() && p.y >= top() && p.y <= bottom();
}
}