#ifndef RESOURCES_H
#define RESOURCES_H

#include "shader_program.h"

#include "buffer_object.h"

class Resources
{
public:
    Resources();
    
    void initShaderProgram(ShaderProgram& program, const char* vertexSrcPath, const char* fragmentSrcPath);
    
    // Shaders stencil
    
    ShaderProgram texture;
    GLint mvpLocationTexture;
    
    ShaderProgram simpleColor;
    GLint mvpLocationSimpleColor;
    
    // Shaders lighting
    ShaderProgram phong;
    GLint mvpLocationPhong;
    GLint modelViewLocationPhong;
    GLint viewLocationPhong;
    GLint normalLocationPhong;

    ShaderProgram gouraud;
    GLint mvpLocationGouraud;
    GLint modelViewLocationGouraud;
    GLint viewLocationGouraud;
    GLint normalLocationGouraud;

    ShaderProgram flat;
    GLint mvpLocationFlat;
    GLint modelViewLocationFlat;
    GLint viewLocationFlat;
    GLint normalLocationFlat;
};

#endif // RESOURCES_H
