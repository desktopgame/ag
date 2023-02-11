#version 120
uniform sampler2D uTexture;
varying vec2 fragTexCoord;
uniform vec4 uColor;

void main() {
    vec4 col = uColor;
    col.a = texture2D(uTexture, fragTexCoord).a;
    gl_FragColor = col;
}