#pragma once
#include <ag/native/glm.hpp>

namespace ag {
class Camera {
public:
    explicit Camera();

    void resize(int width, int height);
    void lookAt(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up);

    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewMatrix() const;

private:
    glm::mat4 m_projMat;
    glm::mat4 m_viewMat;
};
}