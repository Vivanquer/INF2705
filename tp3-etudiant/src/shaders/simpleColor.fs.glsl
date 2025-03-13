#version 330 core

// Texture en entrée
uniform sampler2D textureSampler;

out vec4 FragColor;

void main()
{
    vec2 texCoord = gl_FragCoord.xy / 100.0; 
    
    vec3 texColor = texture(textureSampler, texCoord).rgb;

    vec3 finalColor = texColor * vec3(0.25, 0.8, 1.0);

    FragColor = vec4(finalColor, 1.0);
}