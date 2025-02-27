#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inTexCoord;

uniform mat4 mvpMatrix;
uniform int textureIndex; // Index of the cup in the atlas (0 to 3)
uniform int isPlate;      // 0 = cup, 1 = plate

out vec2 TexCoord;

void main()
{
    gl_Position = mvpMatrix * vec4(inPosition, 1.0);

    // Define atlas structure: 3 columns, 2 rows
    const float COLUMNS = 3.0;
    const float ROWS = 2.0;

    float texWidth = 1.0 / COLUMNS;
    float texHeight = 1.0 / ROWS;
    vec2 texOffset;

    if (isPlate == 0) { // Cup
        float row = floor(textureIndex / 2.0);  // 2 cups per row
        float col = mod(textureIndex, 2.0);     // Only 2 columns for cups
        texOffset = vec2(col * texWidth, row * texHeight);
    } else { // Plate
        texOffset = vec2(2.0 * texWidth, 0.0); // Last column, first row
    }

    TexCoord = inTexCoord * vec2(texWidth, texHeight) + texOffset;
}
