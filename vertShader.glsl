#version 450 core

layout(location = 0) in uint vertData;

out vec2 TexCoord;
out vec2 UvCoord;
out float lighting;

uniform mat4 MVP;
void main()
{
    uint x = bitfieldExtract(vertData, 9, 5);
    //possible issue here
    uint y = bitfieldExtract(vertData, 0, 9);
    uint z = bitfieldExtract(vertData, 14, 5);

    vec3 aPos = vec3(x, y, z);

    uint xUv = bitfieldExtract(vertData, 19, 1);
    uint yUv = bitfieldExtract(vertData, 20, 1);
    UvCoord = vec2(xUv, yUv);

    uint xTex = bitfieldExtract(vertData, 21, 4);
    uint yTex = bitfieldExtract(vertData, 25, 4);
    TexCoord = vec2(xTex, yTex);

    uint occlusionLevel = bitfieldExtract(vertData, 29, 2);
    lighting = 0.75f + 0.1f * occlusionLevel;

    gl_Position = MVP * vec4(aPos, 1.0);
}