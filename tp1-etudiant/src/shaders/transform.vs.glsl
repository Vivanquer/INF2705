#version 330 core

// TODO

layout(location = 0) in vec3 position; // Vertex position
layout(location = 1) in vec3 color;    // Vertex color

uniform mat4 u_MVP; // Model-View-Projection matrix

out vec3 fragColor; // Pass color to fragment shader

void main() {
    gl_Position = u_MVP * vec4(position, 1.0); // Apply transformation
    fragColor = color; // Pass vertex color to the fragment shader
}