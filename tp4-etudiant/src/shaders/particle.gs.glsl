#version 330 core

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;


in ATTRIB_VS_OUT
{
    vec4 color;
    vec2 size;
} attribIn[];

out ATTRIB_GS_OUT
{
    vec4 color;
    vec2 texCoords;
} attribOut;

uniform mat4 projection;

void main()
{
    vec4 center = gl_in[0].gl_Position;
    vec2 size = attribIn[0].size;
    vec4 color = attribIn[0].color;

    vec2 halfSize = size * 0.5;

    // Coin inférieur gauche
    attribOut.color = color;
    attribOut.texCoords = vec2(0.0, 0.0);
    gl_Position = projection * (center + vec4(-halfSize.x, -halfSize.y, 0.0, 0.0));
    EmitVertex();

    // Coin inférieur droit
    attribOut.texCoords = vec2(1.0, 0.0);
    gl_Position = projection * (center + vec4(halfSize.x, -halfSize.y, 0.0, 0.0));
    EmitVertex();

    // Coin supérieur gauche
    attribOut.texCoords = vec2(0.0, 1.0);
    gl_Position = projection * (center + vec4(-halfSize.x, halfSize.y, 0.0, 0.0));
    EmitVertex();

    // Coin supérieur droit
    attribOut.texCoords = vec2(1.0, 1.0);
    gl_Position = projection * (center + vec4(halfSize.x, halfSize.y, 0.0, 0.0));
    EmitVertex();

    EndPrimitive();
}
