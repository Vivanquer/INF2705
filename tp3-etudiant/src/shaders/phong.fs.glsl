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

float getFact(int i, vec3 L, float NdotL) {
    if (!useSpotlight) return 1.0;
    if (NdotL <= 0.0) return 0.0;

    float lightAngle = dot(L, normalize(attribIn.spotDir[i]));
    float outer = cos(radians(spotOpeningAngle));

    if (useDirect3D) {
        float edge = pow(outer, 1.01 + spotExponent / 2);
        if (lightAngle < outer - edge) return 0.0;
        else if (lightAngle > outer) return 1.0;
        else return smoothstep(outer - edge, outer, lightAngle);
    } else if (lightAngle > outer) {
        return pow(lightAngle, spotExponent);
    }
    return 0.0;
}

void main()
{
    vec3 N = normalize(attribIn.normal);
    vec3 O = normalize(attribIn.obsPos);

    vec3 ambient = mat.ambient * lightModelAmbient;
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for (int i = 0; i < lights.length(); i++) {
        vec3 L = normalize(attribIn.lightDir[i]);
        float NdotL = max(dot(N, L), 0.0);
        float factor = getFact(i, L, NdotL);

        if (NdotL > 0.0) {
            diffuse += mat.diffuse * lights[i].diffuse * NdotL * factor;

            float spec = useBlinn ? dot(normalize(L + O), N) : dot(reflect(-L, N), O);
            spec = max(spec, 0.0);
            specular += mat.specular * lights[i].specular * pow(spec, mat.shininess) * factor;
        }

        ambient += mat.ambient * lights[i].ambient;
    }

    vec4 texDiffuse = texture(diffuseSampler, attribIn.texCoords);
    float texSpec = texture(specularSampler, attribIn.texCoords).r;

    if (texDiffuse.a < 0.3)
        discard;

    vec3 color = mat.emission + ambient * texDiffuse.rgb + diffuse * texDiffuse.rgb + specular * texSpec;
    FragColor = vec4(clamp(color, 0.0, 1.0), 1.0);
}
