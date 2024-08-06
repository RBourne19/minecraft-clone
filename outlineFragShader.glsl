#version 450 core

layout(depth_less) out float gl_FragDepth;

in vec2 UvCoord;
out vec4 FragColor;


void main() {
    if (UvCoord.x > 0.01f && UvCoord.y > 0.01f && UvCoord.x < 0.99f && UvCoord.y < 0.99f) discard;

    gl_FragDepth = gl_FragCoord.z - 0.1f;
    FragColor = vec4(1, 1, 1, 1);
}