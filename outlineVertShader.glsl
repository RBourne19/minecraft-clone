#version 450 core

layout(location = 0) in uint vertData;

uniform mat4 MVP;


out vec2 UvCoord;
out vec3 aPos;

void main() {
    uint x = bitfieldExtract(vertData, 9, 5);
    //possible issue here
    uint y = bitfieldExtract(vertData, 0, 9);
    uint z = bitfieldExtract(vertData, 14, 5);

    aPos = vec3(x, y, z);

    uint xUv = bitfieldExtract(vertData, 19, 1);
    uint yUv = bitfieldExtract(vertData, 20, 1);
    UvCoord = vec2(xUv, yUv);

    gl_Position = MVP * vec4(aPos, 1.0);
}