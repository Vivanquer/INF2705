#version 400 core

layout(vertices = 4) out;

uniform mat4 modelView;


const float MIN_TESS = 4;
const float MAX_TESS = 64;

const float MIN_DIST = 30.0f;
const float MAX_DIST = 100.0f;

void main()
{
	// On passe les positions aux shaders suivants
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    barrier(); // Synchronise les threads du patch

    if (gl_InvocationID == 0)
    {
        // Calculer les positions dans le référentiel de la vue
        vec3 p0 = vec3(modelView * gl_in[0].gl_Position);
        vec3 p1 = vec3(modelView * gl_in[1].gl_Position);
        vec3 p2 = vec3(modelView * gl_in[2].gl_Position);
        vec3 p3 = vec3(modelView * gl_in[3].gl_Position);

        // Centres des 4 arêtes (gauche, haut, droite, bas)
        vec3 c0 = (p0 + p1) * 0.5; // gauche
        vec3 c1 = (p1 + p2) * 0.5; // haut
        vec3 c2 = (p2 + p3) * 0.5; // droite
        vec3 c3 = (p3 + p0) * 0.5; // bas

        // Distances de la caméra
        float d0 = length(c0);
        float d1 = length(c1);
        float d2 = length(c2);
        float d3 = length(c3);

        // Interpolation linéaire inversée (proche → MAX_TESS, loin → MIN_TESS)
        float f0 = clamp((d0 - MIN_DIST) / (MAX_DIST - MIN_DIST), 0.0, 1.0);
        float f1 = clamp((d1 - MIN_DIST) / (MAX_DIST - MIN_DIST), 0.0, 1.0);
        float f2 = clamp((d2 - MIN_DIST) / (MAX_DIST - MIN_DIST), 0.0, 1.0);
        float f3 = clamp((d3 - MIN_DIST) / (MAX_DIST - MIN_DIST), 0.0, 1.0);

        float t0 = mix(MAX_TESS, MIN_TESS, f0);
        float t1 = mix(MAX_TESS, MIN_TESS, f1);
        float t2 = mix(MAX_TESS, MIN_TESS, f2);
        float t3 = mix(MAX_TESS, MIN_TESS, f3);

        // Attribuer les facteurs de tessellation
        gl_TessLevelOuter[0] = t0; // gauche
        gl_TessLevelOuter[1] = t1; // haut
        gl_TessLevelOuter[2] = t2; // droite
        gl_TessLevelOuter[3] = t3; // bas

        // Interne : max entre les arêtes opposées
        gl_TessLevelInner[0] = max(t1, t3); // horizontal
        gl_TessLevelInner[1] = max(t0, t2); // vertical
    }

}
