#version 330 core

layout(location = 0) in vec3 aPosition;

uniform mat4 mvpMatrix;

void main()
{
    // mvpMatrix = uProjection * uView * uModel
    gl_Position = mvpMatrix * vec4(aPosition, 1.0);
}