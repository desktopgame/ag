#version 120
uniform sampler2D uTexture;
varying vec2 fragTexCoord;

void main() {
    gl_FragColor = texture2D(uTexture, fragTexCoord);
}