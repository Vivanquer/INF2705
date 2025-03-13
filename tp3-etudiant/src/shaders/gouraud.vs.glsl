#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out ATTRIB_VS_OUT
{
    vec2 texCoords;
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} attribOut;

uniform mat4 mvp;
uniform mat4 view;
uniform mat4 modelView;
uniform mat3 normalMatrix;

struct Material
{
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct UniversalLight
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
    vec3 spotDirection;
};

layout (std140) uniform LightingBlock
{
    Material mat;
    UniversalLight lights[3];
    vec3 lightModelAmbient;
    bool useBlinn;
    bool useSpotlight;
    bool useDirect3D;
    float spotExponent;
    float spotOpeningAngle;
};

void main()
{
    // TODO

    // Transformation du sommet dans l'espace projeté
    gl_Position = mvp * vec4(position, 1.0);
    
    // Transformation des normales en espace de vue
    vec3 fragNormal = normalize(normalMatrix * normal);
    
    // Transformation de la position du sommet en espace de vue
    vec3 fragPosition = (modelView * vec4(position, 1.0)).xyz;
    
    // Initialisation des composantes d'éclairage
    attribOut.ambient = mat.ambient * lightModelAmbient;
    attribOut.diffuse = vec3(0.0);
    attribOut.specular = vec3(0.0);
    
    // Calcul de l'éclairage de Gouraud
    for (int i = 0; i < 3; i++) {
        vec3 lightDir = normalize(lights[i].position - fragPosition);
        float diff = max(dot(fragNormal, lightDir), 0.0);
        attribOut.diffuse += lights[i].diffuse * diff * mat.diffuse;
        
        if (diff > 0.0) {
            vec3 viewDir = normalize(-fragPosition);
            vec3 reflectDir = reflect(-lightDir, fragNormal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
            attribOut.specular += lights[i].specular * spec * mat.specular;
        }
    }
    
    attribOut.emission = mat.emission;
    attribOut.texCoords = texCoords;
}
