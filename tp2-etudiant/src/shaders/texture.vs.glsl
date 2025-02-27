#version 330 core

layout (location = 0) in vec3 aPos;   // Position du sommet
layout (location = 1) in vec2 aTexCoord; // Coordonnées de texture

uniform mat4 mvpMatrix;

out vec2 TexCoord;

void main()
{
    gl_Position = mvpMatrix * vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
