#version 120
attribute vec2 aVertex;
attribute vec2 aTexCoord;
uniform mat4 uTransformMatrix;
varying vec2 fragTexCoord;

void main(void) {
    fragTexCoord = aTexCoord;
    gl_Position = uTransformMatrix * vec4(aVertex, 0, 1);
}