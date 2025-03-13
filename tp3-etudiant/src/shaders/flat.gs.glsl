#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in ATTRIB_OUT
{
    vec3 position;
    vec2 texCoords;
} attribIn[];

out ATTRIB_VS_OUT
{
    vec2 texCoords;    
    vec3 emission;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} attribOut;

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
     // Calcul du vecteur normal du triangle en espace de vue
    vec3 v0 = attribIn[0].position;
    vec3 v1 = attribIn[1].position;
    vec3 v2 = attribIn[2].position;
    
    vec3 normal = normalize(cross(v1 - v0, v2 - v0));
    normal = normalize(normalMatrix * normal);

    // Calcul de la position du triangle dans l'espace de vue
    vec3 facePosition = (modelView * vec4(v0, 1.0)).xyz;

    // Éclairage par face (Flat Shading)
    vec3 ambient = mat.ambient * lightModelAmbient;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    
    for (int i = 0; i < 3; i++) {
        vec3 lightDir = normalize(lights[i].position - facePosition);
        float diff = max(dot(normal, lightDir), 0.0);
        diffuse += lights[i].diffuse * diff;

        if (diff > 0.0) {
            vec3 viewDir = normalize(-facePosition);
            vec3 reflectDir = reflect(-lightDir, normal);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
            specular += lights[i].specular * spec;
        }
    }

    attribOut.ambient = ambient;
    attribOut.diffuse = diffuse * mat.diffuse;
    attribOut.specular = specular * mat.specular;
    attribOut.emission = mat.emission;

    // Émission des sommets avec les mêmes valeurs d'éclairage
    for (int i = 0; i < 3; i++) {
        attribOut.texCoords = attribIn[i].texCoords;
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();
}
