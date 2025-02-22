#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 mvpMatrix;
uniform int textureIndex;
uniform int isPlate; // Remplacer bool par int

out vec2 TexCoord;
flat out int TexIndex;
flat out int IsPlate; // Remplacer bool par int

void main()
{
    gl_Position = mvpMatrix * vec4(inPosition, 1.0);
    TexCoord = inTexCoord;
    TexIndex = textureIndex;
    IsPlate = isPlate; // 0 pour faux, 1 pour vrai
}