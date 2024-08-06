#version 450 core

in float lighting;
in vec2 UvCoord;
out vec4 FragColor;

uniform sampler2D texture1;
void main() {

    vec4 texColor = texture(texture1, ((UvCoord)));

    FragColor = texColor;
}