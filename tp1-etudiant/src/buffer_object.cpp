#include "buffer_object.h"

BufferObject::BufferObject()
{
    glGenBuffers(1, &m_id);
}

BufferObject::BufferObject(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage)
: BufferObject()
{
    allocate(type, dataSize, data, usage);
}

BufferObject::~BufferObject()
{
    glDeleteBuffers(1, &m_id);
}

void BufferObject::bind()
{
    glBindBuffer(m_type, m_id);
}

void BufferObject::unbind() {
    glBindBuffer(m_type, 0); 
}

void BufferObject::allocate(GLenum type, GLsizeiptr dataSize, const void* data, GLenum usage)
{
    m_type = type;
    glBindBuffer(m_type, m_id);
    glBufferData(m_type, dataSize, data, usage);
    glBindBuffer(m_type, 0);
}

void BufferObject::update(GLsizeiptr dataSize, const void* data)
{
    glBindBuffer(m_type, m_id); 
    glBufferSubData(m_type, 0, dataSize, data); 
    glBindBuffer(m_type, 0); 
}

void* BufferObject::mapBuffer(GLenum access)
{
    glBindBuffer(m_type, m_id); // Bind the buffer
    void* ptr = glMapBuffer(m_type, access); // Map buffer memory
    if (!ptr) {
        std::cerr << "Failed to map buffer!" << std::endl;
    }
    return ptr;
}

void BufferObject::unmapBuffer()
{
    glBindBuffer(m_type, m_id); // Bind the buffer
    if (!glUnmapBuffer(m_type)) { // Unmap the buffer
        std::cerr << "Failed to unmap buffer!" << std::endl;
    }
    glBindBuffer(m_type, 0); // Unbind the buffer
}

