#include "resources.h"

#include "shader_program.h"
#include "shader_object.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "utils.h"


Resources::Resources()
{
    // TODO - init des shaders

    // Initialize the texture shader program
    initShaderProgram(texture, "shaders/texture.vert", "shaders/texture.frag");
    mvpLocationTexture = texture.getUniformLoc("mvpMatrix");
    
    // Initialize the color uniform shader program
    initShaderProgram(colorUniform, "shaders/colorUniform.vert", "shaders/colorUniform.frag");
    mvpLocationColorUniform = colorUniform.getUniformLoc("mvpMatrix");
    colorLocationColorUniform = colorUniform.getUniformLoc("color");
    
    // Initialize the cup shader program
    initShaderProgram(cup, "shaders/cup.vert", "shaders/cup.frag");
    mvpLocationCup = cup.getUniformLoc("mvpMatrix");
    textureIndexLocationCup = cup.getUniformLoc("textureIndex");
    isPlateLocationCup = cup.getUniformLoc("isPlate");
}

void Resources::initShaderProgram(ShaderProgram& program, const char* vertexSrcPath, const char* fragmentSrcPath)
{
    // --- Read the vertex shader source code ---
    std::string vertexCode;
    std::ifstream vertexFile(vertexSrcPath);
    if (!vertexFile.is_open())
    {
        std::cerr << "Error: Failed to open vertex shader file: " << vertexSrcPath << std::endl;
        return;
    }
    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    vertexFile.close();
    vertexCode = vertexStream.str();

    // --- Read the fragment shader source code ---
    std::string fragmentCode;
    std::ifstream fragmentFile(fragmentSrcPath);
    if (!fragmentFile.is_open())
    {
        std::cerr << "Error: Failed to open fragment shader file: " << fragmentSrcPath << std::endl;
        return;
    }
    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    fragmentFile.close();
    fragmentCode = fragmentStream.str();

    // --- Create shader objects ---
    ShaderObject vertexShader(GL_VERTEX_SHADER, vertexCode.c_str());
    ShaderObject fragmentShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    // --- Attach shader objects to the shader program ---
    program.attachShaderObject(vertexShader);
    program.attachShaderObject(fragmentShader);

    // --- Link the shader program ---
    program.link();
}

