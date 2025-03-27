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

vec4 interpole( vec4 v0, vec4 v1, vec4 v2, vec4 v3 )
{
    // mix( x, y, f ) = x * (1-f) + y * f.
    // TODO
    return vec4(0.0f);
}


const float PLANE_SIZE = 256.0f;

void main()
{
	// TODO
}
