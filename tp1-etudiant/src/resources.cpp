#include "resources.h"

#include "utils.h"

#include "shader_object.h"

#include "vertices_data.h"

Resources::Resources() {
    // Initialize the basic shader program
    initShaderProgram(basic, "shaders/basic.vs.glsl", "shaders/basic.fs.glsl");

    // Initialize the color shader program
    initShaderProgram(color, "shaders/color.vs.glsl", "shaders/color.fs.glsl");

    // Initialize the transform shader program
    initShaderProgram(transform, "shaders/transform.vs.glsl", "shaders/transform.fs.glsl");

    // Get the location of the MVP matrix uniform in the transform shader program
    transform.use(); // Use the transform shader program
    mvpLocation = glGetUniformLocation(transform.getID(), "u_MVP");

    // Initialize buffer objects
    // Colored triangle buffer
    coloredTriangleBuffer.allocate(
        GL_ARRAY_BUFFER, 
        sizeof(colorTriVertices), 
        colorTriVertices, 
        GL_STATIC_DRAW
    );

    // Colored square buffer
    coloredSquareBuffer.allocate(
        GL_ARRAY_BUFFER, 
        sizeof(colorSquareVertices), 
        colorSquareVertices, 
        GL_STATIC_DRAW
    );

    // Colored square reduced buffer
    coloredSquareReduceBuffer.allocate(
        GL_ARRAY_BUFFER, 
        sizeof(colorSquareVerticesReduced), 
        colorSquareVerticesReduced, 
        GL_STATIC_DRAW
    );

    // Colored square reduced indices buffer
    coloredSquareIndicesBuffer.allocate(
        GL_ELEMENT_ARRAY_BUFFER, 
        sizeof(indexes), 
        indexes, 
        GL_STATIC_DRAW
    );
}

void Resources::initShaderProgram(ShaderProgram& program, const char* vertexSrcPath, const char* fragmentSrcPath) {
    // Read vertex and fragment shader source code from files
    std::string vertexSource = readFile(vertexSrcPath);
    std::string fragmentSource = readFile(fragmentSrcPath);

    // Create and compile shader objects
    ShaderObject vertexShader(GL_VERTEX_SHADER, vertexSource.c_str());
    ShaderObject fragmentShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    // Attach shaders to the program
    program.attachShaderObject(vertexShader);
    program.attachShaderObject(fragmentShader);

    // Link the shader program
    program.link();
}