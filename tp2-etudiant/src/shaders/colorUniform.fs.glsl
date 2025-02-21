#version 330 core

// TODO

out vec4 FragColor; // Couleur finale du fragment

uniform vec3 uColor; // Couleur du modèle

void main()
{
    FragColor = vec4(uColor, 1.0); // Applique la couleur définie en uniforme
}