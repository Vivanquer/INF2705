#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>

class ShaderObject;

class ShaderProgram
{
public:
    ShaderProgram(const char* name);
    ~ShaderProgram();
    
    void use();
    void attachShaderObject(ShaderObject& s);
    void link();
    
    GLint getUniformLoc(const char* name);
    
    void setUniformBlockBinding(const char* name, GLuint bindingIndex);
    
    void setTransformFeedbackVaryings(const char** names, GLsizei number, GLenum mode);
    
private:
    void checkLinkingError();

private:
    GLuint m_id;
    const char* m_name;
};


#endif // SHADER_PROGRAM_H
