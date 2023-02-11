#version 120
uniform sampler2D uTexture;
uniform vec4 uColor;
varying vec2 fragTexCoord;

void main() {
    gl_FragColor = texture2D(uTexture, fragTexCoord) * uColor;
}