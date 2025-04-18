#ifndef RESOURCES_H
#define RESOURCES_H

#include "shader_program.h"

#include "buffer_object.h"

class Resources
{
public:
    Resources();

    // Shaders
    ShaderProgram basic;
    ShaderProgram color;
    
    ShaderProgram transform; 
    GLint mvpLocation;
    
    // Buffer Objects    
    BufferObject coloredTriangleBuffer;
    BufferObject coloredSquareBuffer;
    BufferObject coloredSquareReduceBuffer;
    BufferObject coloredSquareIndexesBuffer;
    BufferObject coloredSharedBuffer;
    BufferObject coloredSquareIndicesBuffer;

    BufferObject cubeBuffer;       // VBO for cube vertices
    BufferObject cubeIndicesBuffer; // EBO for cube indices

private:    
    void initShaderProgram(ShaderProgram& program, const char* vertexSrcPath, const char* fragmentSrcPath);
    
};

#endif // RESOURCES_H
