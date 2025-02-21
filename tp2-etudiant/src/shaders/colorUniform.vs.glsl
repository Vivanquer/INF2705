#version 330 core

// TODO

layout(location = 0) in vec3 aPosition; // Position du sommet

uniform mat4 uModel;      // Matrice de transformation du modèle
uniform mat4 uView;       // Matrice de vue
uniform mat4 uProjection; // Matrice de projection

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}