#include "shader_program.h"

#include <iostream>
#include "shader_object.h"

ShaderProgram::ShaderProgram()
{
    m_id = glCreateProgram();
}
    
ShaderProgram::~ShaderProgram()
{   
    if(m_id != 0) {
        glDeleteProgram(m_id);
    }
}
    
void ShaderProgram::use()
{
    glUseProgram(m_id);
}
    
void ShaderProgram::attachShaderObject(ShaderObject& s)
{        
    glAttachShader(m_id, s.id());
}
    
void ShaderProgram::link()
{
    glLinkProgram(m_id);
    checkLinkingError();
}

GLint ShaderProgram::getUniformLoc(const char* name)
{
    return glGetUniformLocation(m_id, name);
}

GLuint ShaderProgram::getID() const { return m_id; }
    
void ShaderProgram::checkLinkingError()
{
    GLint success;
    GLchar infoLog[1024];

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_id, 1024, NULL, infoLog);
        glDeleteProgram(m_id);
        std::cout << "Program linking error: " << infoLog << std::endl;
    }
}
