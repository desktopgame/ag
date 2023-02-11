#version 120
attribute vec3 aVertex;
uniform mat4 uTransformMatrix;

void main(void) {
    gl_Position = uTransformMatrix * vec4(aVertex, 1);
}