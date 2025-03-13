#version 330 core

in ATTRIB_VS_OUT
{
    vec2 texCoords;
    vec3 normal;
    vec3 lightDir[3];
    vec3 spotDir[3];
    vec3 obsPos;
} attribIn;

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

uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;

out vec4 FragColor;

void main()
{
    // TODO

    vec3 norm = normalize(attribIn.normal);
    vec3 viewDir = normalize(attribIn.obsPos);
    vec3 ambient = mat.ambient * lightModelAmbient;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    
    for (int i = 0; i < 3; i++) {
        vec3 lightDirection = normalize(attribIn.lightDir[i]);
        float diff = max(dot(norm, lightDirection), 0.0);
        diffuse += lights[i].diffuse * diff * mat.diffuse;
        
        if (diff > 0.0) {
            vec3 reflectDir = reflect(-lightDirection, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
            specular += lights[i].specular * spec * mat.specular;
        }
    }
    
    vec3 texDiffuse = texture(diffuseSampler, attribIn.texCoords).rgb * diffuse;
    vec3 texSpecular = texture(specularSampler, attribIn.texCoords).rgb * specular;
    
    vec3 finalColor = mat.emission + ambient + texDiffuse + texSpecular;
    FragColor = vec4(finalColor, 1.0);
}



