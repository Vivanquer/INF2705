#ifndef RESOURCES_H
#define RESOURCES_H

#include "shader_program.h"

#include "buffer_object.h"

class Resources
{
public:
    Resources();
    
    void initShaderProgram(ShaderProgram& program, const char* vertexSrcPath, const char* fragmentSrcPath);
    
    // Shaders    
    ShaderProgram texture; 
    GLint mvpLocationTexture;
    
    ShaderProgram colorUniform; 
    GLint mvpLocationColorUniform;
    GLint colorLocationColorUniform;
    
    ShaderProgram cup;
    GLint mvpLocationCup;
    GLint textureIndexLocationCup;
    GLint isPlateLocationCup;
};

#endif // RESOURCES_H
