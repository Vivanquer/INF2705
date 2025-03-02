#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 mvpMatrix;
uniform int textureIndex; 
uniform int isPlate;      

out vec2 TexCoord;

void main()
{
    gl_Position = mvpMatrix * vec4(inPosition, 1.0);

    const float COLUMNS = 3.0;
    const float ROWS = 2.0;

    float texWidth = 1.0 / COLUMNS;
    float texHeight = 1.0 / ROWS;
    vec2 texOffset;

    if (isPlate == 0) { 
        float row = floor(textureIndex / 2.0);  
        float col = mod(textureIndex, 2.0);     
        texOffset = vec2(col * texWidth, row * texHeight);
    } else { // Plate
        texOffset = vec2(2.0 * texWidth, 0.0); 
    }

    TexCoord = inTexCoord * vec2(texWidth, texHeight) + texOffset;
}
