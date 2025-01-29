#include "draw_commands.h"


DrawArraysCommand::DrawArraysCommand(VertexArrayObject& vao, GLsizei count)
: m_vao(vao), m_count(count) {}

void DrawArraysCommand::draw()
{
    m_vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, m_count); // Default to GL_TRIANGLES, change if needed
    m_vao.unbind();
}

void DrawArraysCommand::setCount(GLsizei count)
{
    m_count = count;
}

DrawElementsCommand::DrawElementsCommand(VertexArrayObject& vao, GLsizei count, GLenum type)
: m_vao(vao), m_count(count), m_type(type) {}

void DrawElementsCommand::draw()
{
    m_vao.bind();
    glDrawElements(GL_TRIANGLES, m_count, m_type, nullptr); // Default to GL_TRIANGLES
    m_vao.unbind();
}

void DrawElementsCommand::setCount(GLsizei count)
{
    m_count = count;
}


