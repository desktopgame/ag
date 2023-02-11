#version 120
attribute vec2 aVertex;
uniform mat4 uTransformMatrix;

void main(void) {
    gl_Position = uTransformMatrix * vec4(aVertex, 0, 1);
}