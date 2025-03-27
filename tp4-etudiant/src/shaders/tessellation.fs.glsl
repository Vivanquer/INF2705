#version 330 core

in ATTRIB_GS_OUT
{
    float height;
    vec2 texCoords;
    vec4 patchDistance;
    vec3 barycentricCoords;
} attribIn;

uniform sampler2D groundSampler;
uniform sampler2D sandSampler;
uniform sampler2D snowSampler;
uniform bool viewWireframe;

out vec4 FragColor;

float edgeFactor(vec3 barycentricCoords, float width)
{
    vec3 d = fwidth(barycentricCoords);
    vec3 f = step(d * width, barycentricCoords);
    return min(min(f.x, f.y), f.z);
}

float edgeFactor(vec4 barycentricCoords, float width)
{
    vec4 d = fwidth(barycentricCoords);
    vec4 f = step(d * width, barycentricCoords);
    return min(min(min(f.x, f.y), f.z), f.w);
}

const vec3 WIREFRAME_COLOR = vec3(0.5f);
const vec3 PATCH_EDGE_COLOR = vec3(1.0f, 0.0f, 0.0f);

const float WIREFRAME_WIDTH = 0.5f;
const float PATCH_EDGE_WIDTH = 0.5f;

void main()
{
	float h = attribIn.height;

    // Blend entre les textures selon la hauteur
    float sandFactor  = 1.0 - smoothstep(0.3, 0.35, h);
    float grassFactor = smoothstep(0.3, 0.35, h) * (1.0 - smoothstep(0.6, 0.65, h));
    float snowFactor  = smoothstep(0.6, 0.65, h);

    vec4 sandTex  = texture(sandSampler, attribIn.texCoords * 2.0);
    vec4 grassTex = texture(groundSampler, attribIn.texCoords * 2.0);
    vec4 snowTex  = texture(snowSampler, attribIn.texCoords * 2.0);

    vec4 baseColor = 
        sandFactor  * sandTex +
        grassFactor * grassTex +
        snowFactor  * snowTex;

    // Fil de fer et contour de patch
    float triangleEdge = edgeFactor(attribIn.barycentricCoords, WIREFRAME_WIDTH);
    float patchEdge    = edgeFactor(attribIn.patchDistance, PATCH_EDGE_WIDTH);

    if (viewWireframe) {
        vec3 finalColor = mix(WIREFRAME_COLOR, baseColor.rgb, triangleEdge);
        finalColor = mix(PATCH_EDGE_COLOR, finalColor, patchEdge);
        FragColor = vec4(finalColor, 1.0);
    } else {
        FragColor = baseColor;
    }
}
