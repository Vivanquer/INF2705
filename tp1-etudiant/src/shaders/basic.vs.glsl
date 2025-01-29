#version 330 core

// TODO
layout(location = 0) in vec3 position;

void main() {
    // Assignation de gl_Position (passage à l'espace clip)
    gl_Position = vec4(position, 1.0);
}