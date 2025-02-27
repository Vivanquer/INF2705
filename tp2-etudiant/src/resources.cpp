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
    initShaderProgram(texture, "./shaders/texture.vs.glsl", "./shaders/texture.fs.glsl");
    mvpLocationTexture = texture.getUniformLoc("mvpMatrix");
    if (mvpLocationTexture == -1) {
        std::cerr << "mvpLocationTexture Uniform `mvpMatrix` introuvable dans `texture.vs.glsl` !" << std::endl;
    }

    // Initialize the color uniform shader program
    initShaderProgram(colorUniform, "./shaders/colorUniform.vs.glsl", "./shaders/colorUniform.fs.glsl");
    mvpLocationColorUniform = colorUniform.getUniformLoc("mvpMatrix");
    // colorLocationColorUniform = colorUniform.getUniformLoc("mvpMatrix");
    if (mvpLocationColorUniform == -1) {
        std::cerr << "mvpLocationColorUniform Uniform `mvpMatrix` introuvable !" << std::endl;
    }
    if (colorLocationColorUniform == -1) {
        std::cerr << "colorLocationColorUniform Uniform `FragColor` introuvable" << std::endl;
    }

    // Initialize the cup shader program
    initShaderProgram(cup, "./shaders/cup.vs.glsl", "./shaders/colorUniform.fs.glsl");
    mvpLocationCup = cup.getUniformLoc("mvpMatrix");
    // textureIndexLocationCup = cup.getUniformLoc("textureIndex");
    // isPlateLocationCup = cup.getUniformLoc("isPlate");

    if (mvpLocationCup == -1) {
        std::cerr << "mvpLocationCup Uniform `mvpMatrix` introuvable" << std::endl;
    }
    // if (textureIndexLocationCup == -1) {
    //     std::cerr << "textureIndexLocationCup Uniform `textureIndex` introuvable!" << std::endl;
    // }
    // if (isPlateLocationCup == -1) {
    //     std::cerr << "isPlateLocationCup Uniform `isPlate` introuvable!" << std::endl;
    // }
}

// void Resources::initShaderProgram(ShaderProgram& program, const char* vertexSrcPath, const char* fragmentSrcPath)
// {
//     // --- Read the vertex shader source code ---
//     std::string vertexCode;
//     std::ifstream vertexFile(vertexSrcPath);
//     if (!vertexFile.is_open())
//     {
//         std::cerr << "Error: Failed to open vertex shader file: " << vertexSrcPath << std::endl;
//         return;
//     }
//     std::stringstream vertexStream;
//     vertexStream << vertexFile.rdbuf();
//     vertexFile.close();
//     vertexCode = vertexStream.str();

//     // --- Read the fragment shader source code ---
//     std::string fragmentCode;
//     std::ifstream fragmentFile(fragmentSrcPath);
//     if (!fragmentFile.is_open())
//     {
//         std::cerr << "Error: Failed to open fragment shader file: " << fragmentSrcPath << std::endl;
//         return;
//     }
//     std::stringstream fragmentStream;
//     fragmentStream << fragmentFile.rdbuf();
//     fragmentFile.close();
//     fragmentCode = fragmentStream.str();

//     // --- Create shader objects ---
//     ShaderObject vertexShader(GL_VERTEX_SHADER, vertexCode.c_str());
//     ShaderObject fragmentShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

//     // --- Attach shader objects to the shader program ---
//     program.attachShaderObject(vertexShader);
//     program.attachShaderObject(fragmentShader);

//     // --- Link the shader program ---
//     program.link();
// }

