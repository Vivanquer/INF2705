#version 330 core

out vec4 FragColor;


uniform sampler2D textureSampler;

in ATTRIB_GS_OUT
{
    vec4 color;
    vec2 texCoords;
} attribIn;

void main()
{
    // TODO
}
