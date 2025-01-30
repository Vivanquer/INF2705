#version 330 core

// TODO

in vec3 fragColor; // Receive color from vertex shader
out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0); // Output color with full alpha
}