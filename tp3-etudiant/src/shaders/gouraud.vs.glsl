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

float getFact(int i, vec3 L, float NdotL) {
    if (!useSpotlight) {
        return 1.0;
    }

    if (NdotL <= 0.0)
        return 0.0;

    float lightAngle = dot(L, mat3(view) * (-lights[i].spotDirection)); // dot(L, Ln) -> cos(γ)
    float outer = cos(radians(spotOpeningAngle));


    if (useDirect3D) {
            if (lightAngle < outer - pow(outer, 1.01 + spotExponent/2))
                return 0.0;
            else if (lightAngle > outer)
                return 1.0;
            else
                return smoothstep(pow(outer, 1.01 + spotExponent/2), outer, lightAngle);
    } else if (lightAngle > outer) {
        return pow(lightAngle, spotExponent);
    }
    return 0.0;
}


void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    attribOut.texCoords = texCoords;
    attribOut.emission = mat.emission;
    attribOut.ambient = mat.ambient * lightModelAmbient;
    attribOut.diffuse = vec3(0.0, 0.0, 0.0);
    attribOut.specular = vec3(0.0, 0.0, 0.0);

    vec3 pos = vec3(modelView * vec4(position, 1.0));

    vec3 N = normalize(normalMatrix * normal);
    vec3 O = normalize(-pos);


    for(int i = 0; i < lights.length(); i++) {
        vec3 L = normalize((view * vec4(lights[i].position, 1.0)).xyz - pos);
        float NdotL = max(0.0, dot(N, L));

        attribOut.ambient += mat.ambient * lights[i].ambient; // Ambient

        float fact = getFact(i, L, NdotL);
        if (NdotL > 0.0) {
            attribOut.diffuse += mat.diffuse * lights[i].diffuse * NdotL * fact; // Diffuse
        }
        float spec = useBlinn ? dot(normalize(L + O), N) : dot(reflect(-L, N), O);
        if (spec > 0)
            attribOut.specular += mat.specular * lights[i].specular * pow(spec, mat.shininess) * fact; // Specular
    }
}
