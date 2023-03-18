#include <ag/graphics/MatrixStack.hpp>

namespace ag {

MatrixStack::MatrixStack()
    : m_stack()
{
}
void MatrixStack::push(const glm::mat4& m)
{
    m_stack.emplace_back(m);
}
glm::mat4 MatrixStack::top() const { return m_stack.back(); }
void MatrixStack::pop() { m_stack.pop_back(); }
glm::mat4 MatrixStack::mult() const
{
    glm::mat4 m(1.0f);
    auto iter = m_stack.begin();
    while (iter != m_stack.end()) {
        m = m * (*iter);
        ++iter;
    }
    return m;
}
void MatrixStack::clear()
{
    m_stack.clear();
}

}
