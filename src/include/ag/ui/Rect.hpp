#pragma once
#include <ag/native/glm.hpp>

namespace agui {
class Rect {
public:
    explicit Rect();
    explicit Rect(const glm::ivec2& position, const glm::ivec2& size);
    glm::ivec2 position;
    glm::ivec2 size;

    int left() const;
    int right() const;
    int top() const;
    int bottom() const;

    bool contains(const glm::ivec2& p) const;
};
}