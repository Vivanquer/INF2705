#version 330 core

in ATTRIB_VS_OUT
{
    vec2 texCoords;
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} attribIn;

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;

out vec4 FragColor;

void main()
{
    // TODO

    // Échantillonnage des textures diffuse et spéculaire
    vec3 diffuseColor = texture(diffuseSampler, attribIn.texCoords).rgb * attribIn.diffuse;
    vec3 specularColor = texture(specularSampler, attribIn.texCoords).rgb * attribIn.specular;
    
    // Calcul de la couleur finale
    vec3 finalColor = attribIn.emission + attribIn.ambient + diffuseColor + specularColor;
    
    FragColor = vec4(finalColor, 1.0);
}
