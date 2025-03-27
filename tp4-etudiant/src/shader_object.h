#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include <GL/glew.h>

class ShaderObject
{
public:
    ShaderObject(const char* name, GLenum type, const char* code);
    ~ShaderObject();
    
    GLuint id();
    
private:
    void checkCompilingError(const char* name);
    
private:
    GLuint m_id;
};

#endif // SHADER_OBJECT_H
