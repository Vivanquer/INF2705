#version 400 core

layout(quads) in;

/*
in Attribs {
    vec4 couleur;
} AttribsIn[];*/


out ATTRIB_TES_OUT
{
    float height;
    vec2 texCoords;
    vec4 patchDistance;
} attribOut;

uniform mat4 mvp;

uniform sampler2D heighmapSampler;

vec4 interpole(vec4 v0, vec4 v1, vec4 v2, vec4 v3)
{
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    vec4 a = mix(v0, v3, u);
    vec4 b = mix(v1, v2, u);
    return mix(a, b, v); // interpolation bilinéaire
}


const float PLANE_SIZE = 256.0f;

void main()
{
	// Interpolation des positions
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;
    vec4 p2 = gl_in[2].gl_Position;
    vec4 p3 = gl_in[3].gl_Position;

    vec4 position = interpole(p0, p1, p2, p3);

    // Coordonnées de texture [0,1]
    vec2 texCoord = (position.xz + vec2(PLANE_SIZE * 0.5)) / PLANE_SIZE;
    vec2 texCoordScaled = texCoord / 4.0; // étirer texture

    float h = texture(heighmapSampler, texCoordScaled).r;
    float height = mix(-32.0, 32.0, h); // convertit [0,1] → [-32, 32]
    position.y = height;

    gl_Position = mvp * position;

    attribOut.height = h;
    attribOut.texCoords = texCoord;
    attribOut.patchDistance = vec4(gl_TessCoord.xy, 1.0 - gl_TessCoord.xy);
}
