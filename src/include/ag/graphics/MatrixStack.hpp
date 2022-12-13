#pragma once
#include <ag/native/glm.hpp>
#include <vector>

namespace ag {
class MatrixStack {
public:
    explicit MatrixStack();
    void push(const glm::mat4& m);
    glm::mat4 top() const;
    void pop();
    glm::mat4 mult() const;
    void clear();

private:
    std::vector<glm::mat4> m_stack;
};
}
