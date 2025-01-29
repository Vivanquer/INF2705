#version 330 core

// TODO
// Input from vertex shader
in vec3 fragColor;

// Output to the framebuffer
out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0); // Use the color from the vertex shader and set alpha to 1.0
}