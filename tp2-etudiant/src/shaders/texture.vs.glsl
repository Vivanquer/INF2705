#version 330 core

// TODO

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 mvpMatrix;

out vec2 TexCoord;

void main()
{
    gl_Position = mvpMatrix * vec4(inPosition, 1.0);
    TexCoord = inTexCoord;
}