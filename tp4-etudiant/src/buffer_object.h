#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include <GL/glew.h>

class BufferObject
{
public:
    BufferObject();
    BufferObject(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage);
    ~BufferObject();

    void bind();
    
    void allocate(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage);
    
    void update(GLsizeiptr dataSize, const void* data);
    
    void* mapBuffer();
    void unmapBuffer();
    
private:
    GLuint m_id;
    GLenum m_type;
};

#endif // BUFFER_OBJECT_H
