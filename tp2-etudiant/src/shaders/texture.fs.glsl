#version 330 core

// TODO

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D textureSampler;

void main()
{
    FragColor = texture(textureSampler, TexCoord);
}