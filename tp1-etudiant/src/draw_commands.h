#ifndef DRAW_COMMANDS_H
#define DRAW_COMMANDS_H

#include <GL/glew.h>

#include "vertex_array_object.h"

class DrawArraysCommand
{
public:
    DrawArraysCommand(VertexArrayObject& vao, GLsizei count);
    void draw();
    
    void setCount(GLsizei count);
private:
    VertexArrayObject& m_vao;
    GLsizei m_count;
};


class DrawElementsCommand
{
public:
    DrawElementsCommand(VertexArrayObject& vao, GLsizei count, GLenum type = GL_UNSIGNED_BYTE);
    void draw();
    
    void setCount(GLsizei count);
private:
    VertexArrayObject& m_vao;
    GLsizei m_count;
    GLenum m_type;
};

#endif // DRAW_COMMANDS_H
