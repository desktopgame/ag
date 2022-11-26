#pragma once
#include <string>

namespace ag {
namespace internal {
    static constexpr inline const char* GL_ColorVertexShader = R"(
        #version 120
        attribute vec2 aVertex;
        uniform mat4 uTransformMatrix;

        void main(void) {
            gl_Position = uTransformMatrix * vec4(aVertex, 0, 1);
        }
    )";
    static constexpr inline const char* GL_ColorFragmentShader = R"(
        #version 120
        uniform vec4 uColor1;

        void main() {
            gl_FragColor = uColor1;
        }
    )";
}
}