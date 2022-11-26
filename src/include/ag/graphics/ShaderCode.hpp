#pragma once
#include <string>

namespace ag {
namespace internal {
    static constexpr inline const char* GL_RectVertexShader = R"(
        #version 120
        attribute vec2 aVertex;
        uniform mat4 uTransformMatrix;

        void main(void) {
            gl_Position = uTransformMatrix * vec4(aVertex, 0, 1);
        }
    )";
    static constexpr inline const char* GL_RectFragmentShader = R"(
        #version 120
        // out vec4 outputColor;

        void main() {
            gl_FragColor = vec4(1, 0, 0, 1);
        }
    )";
}
}