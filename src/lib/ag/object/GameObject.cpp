#include <ag/object/GameObject.hpp>
#include <algorithm>

namespace ag {
GameObject::Instance GameObject::create(const std::string& name)
{
    auto ret = std::shared_ptr<GameObject>(new GameObject());
    ret->setName(name);
    return ret;
}
void GameObject::update(const ag::InputState& input, float deltaTime)
{
    // add reserved components
    for (auto a : m_addBuffer) {
        m_components.emplace_back(a);
    }
    m_addBuffer.clear();
    // remove reserved components
    for (auto r : m_removeBuffer) {
        auto iter = std::remove_if(m_components.begin(), m_components.end(), [r](Component::Instance e) -> bool {
            return e == r;
        });
        m_components.erase(iter, m_components.end());
    }
    m_removeBuffer.clear();
    // update components
    for (auto c : m_components) {
        c->update(input, deltaTime);
    }
}
void GameObject::draw(const ag::Renderer::Instance& renderer)
{
    for (auto c : m_components) {
        c->draw(renderer);
    }
}

void GameObject::addComponent(const Component::Instance& c)
{
    m_addBuffer.emplace_back(c);
    c->start();
}

void GameObject::removeComponent(const Component::Instance& c)
{
    m_removeBuffer.emplace_back(c);
    c->onDestroy();
}
std::vector<Component::Instance> GameObject::getComponents() const { return m_components; }

void GameObject::setName(const std::string& name) { m_name = name; }
std::string GameObject::getName() const { return m_name; }

void GameObject::setTag(const std::string& tag) { m_tag = tag; }
std::string GameObject::getTag() const { return m_tag; }

void GameObject::setPosition(const glm::vec3& position) { m_position = position; }
glm::vec3 GameObject::getPosition() const { return m_position; }

void GameObject::setRotation(const glm::vec3& rotation) { m_rotation = rotation; }
glm::vec3 GameObject::getRotation() const { return m_rotation; }

void GameObject::setScale(const glm::vec3& scale) { m_scale = scale; }
glm::vec3 GameObject::getScale() const { return m_scale; }

void GameObject::destroy()
{
    if (m_isDestroyed) {
        return;
    }
    m_isDestroyed = true;
    for (auto c : m_components) {
        c->onDestroy();
    }
    m_components.clear();
}
bool GameObject::isDestroyed() const { return m_isDestroyed; }
// private
GameObject::GameObject()
    : m_components()
    , m_addBuffer()
    , m_removeBuffer()
    , m_name("")
    , m_tag("")
    , m_position()
    , m_rotation()
    , m_scale(1, 1, 1)
    , m_isDestroyed(false)
{
}
}