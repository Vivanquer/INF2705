#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in ATTRIB_TES_OUT
{
    float height;
    vec2 texCoords;
    vec4 patchDistance;
} attribIn[];

out ATTRIB_GS_OUT
{
    float height;
    vec2 texCoords;
    vec4 patchDistance;
    vec3 barycentricCoords;
} attribOut;

void main()
{
    // TODO
}
