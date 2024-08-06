#version 450 core

const ivec2 atlasDimensions = ivec2(16, 16); 
const vec2 tileSize = vec2(1.0 / 16.0);


out vec4 FragColor;

in float lighting;
in vec2 TexCoord;
in vec2 UvCoord;

uniform sampler2D texture1;
void main() {

    vec4 texColor = texture(texture1, ((TexCoord * tileSize) + (UvCoord * tileSize))) * lighting;
    texColor.a = 1;
    FragColor = texColor;
}