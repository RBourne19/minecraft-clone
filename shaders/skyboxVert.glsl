#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 uv;
out vec2 UvCoord;
out float lighting;

uniform mat4 transform;
void main()
{
    UvCoord = uv;

    lighting = 1;
    vec4 pos = transform * vec4(aPos, 1.0);
    gl_Position = pos;
}