#include <ag/graphics/Camera.hpp>

namespace ag {
Camera::Camera()
    : m_projMat(1.0f)
    , m_viewMat(1.0f)
{
    lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 0, 0), glm::vec3(0, -1, 0));
}

void Camera::resize(int width, int height)
{
    float fWidth = static_cast<float>(width);
    float fHeight = static_cast<float>(height);
    m_projMat = glm::perspective(30.f, fWidth / fHeight, 1.f, 1000.f);
}

void Camera::lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up)
{
    m_viewMat = glm::lookAt(eye, center, up);
}
glm::mat4 Camera::getProjectionMatrix() const { return m_projMat; }
glm::mat4 Camera::getViewMatrix() const { return m_viewMat; }

}