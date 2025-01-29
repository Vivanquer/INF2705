#version 330 core

// TODO

layout(location = 0) in vec3 position; // Vertex position
layout(location = 1) in vec3 color;    // Vertex color

out vec3 fragColor;

void main() {
    gl_Position = vec4(position, 1.0); // Pass the vertex position to the pipeline
    fragColor = color;                // Pass the vertex color to the fragment shader
}