#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include "buffer_object.h"

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();

    void bind();
    void unbind();
    
    void specifyAttribute(BufferObject& buffer, GLuint index, GLint size, GLsizei stride, GLsizeiptr offset);
    
private:
    GLuint m_id;
};

#endif // VERTEX_ARRAY_OBJECT_H
