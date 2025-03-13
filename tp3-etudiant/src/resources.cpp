#include "resources.h"

#include "utils.h"

#include "shader_object.h"

#include <iostream>

// Rien à faire ici, modification au besoin, mais ne devrait pas être le cas

Resources::Resources()
: texture("Texture")
, simpleColor("SimpleColor")
, phong("Phong")
, gouraud("Gouraud")
, flat("Flat")
{
    ShaderObject vertexT("texture.vs.glsl", GL_VERTEX_SHADER, readFile("shaders/texture.vs.glsl").c_str());
    ShaderObject fragmentT("texture.fs.glsl", GL_FRAGMENT_SHADER, readFile("shaders/texture.fs.glsl").c_str());
    texture.attachShaderObject(vertexT);
    texture.attachShaderObject(fragmentT);
    texture.link();
    mvpLocationTexture = texture.getUniformLoc("mvp");
    
    ShaderObject vertexS("simpleColor.vs.glsl", GL_VERTEX_SHADER, readFile("shaders/simpleColor.vs.glsl").c_str());
    ShaderObject fragmentS("simpleColor.fs.glsl", GL_FRAGMENT_SHADER, readFile("shaders/simpleColor.fs.glsl").c_str());
    simpleColor.attachShaderObject(vertexS);
    simpleColor.attachShaderObject(fragmentS);
    simpleColor.link();
    mvpLocationSimpleColor = simpleColor.getUniformLoc("mvp");
    
    ShaderObject vertex("phong.vs.glsl", GL_VERTEX_SHADER, readFile("shaders/phong.vs.glsl").c_str());
    ShaderObject fragment("phong.fs.glsl", GL_FRAGMENT_SHADER, readFile("shaders/phong.fs.glsl").c_str());
    phong.attachShaderObject(vertex);
    phong.attachShaderObject(fragment);
    phong.link();
        
    phong.use();
    glUniform1i(phong.getUniformLoc("diffuseSampler"), 0);
    glUniform1i(phong.getUniformLoc("specularSampler"), 1);

    mvpLocationPhong = phong.getUniformLoc("mvp");
    modelViewLocationPhong = phong.getUniformLoc("modelView");
    viewLocationPhong = phong.getUniformLoc("view");
    normalLocationPhong = phong.getUniformLoc("normalMatrix");
    
    ShaderObject vertexG("gouraud.vs.glsl", GL_VERTEX_SHADER, readFile("shaders/gouraud.vs.glsl").c_str());    
    ShaderObject fragmentG("gouraud.fs.glsl", GL_FRAGMENT_SHADER, readFile("shaders/gouraud.fs.glsl").c_str());
    gouraud.attachShaderObject(vertexG);
    gouraud.attachShaderObject(fragmentG);
    gouraud.link();

    gouraud.use();
    glUniform1i(gouraud.getUniformLoc("diffuseSampler"), 0);
    glUniform1i(gouraud.getUniformLoc("specularSampler"), 1);
        
    mvpLocationGouraud = gouraud.getUniformLoc("mvp");
    modelViewLocationGouraud = gouraud.getUniformLoc("modelView");
    viewLocationGouraud = gouraud.getUniformLoc("view");
    normalLocationGouraud = gouraud.getUniformLoc("normalMatrix");

    ShaderObject vertexF("flat.vs.glsl", GL_VERTEX_SHADER, readFile("shaders/flat.vs.glsl").c_str());
    ShaderObject geomF("flat.gs.glsl", GL_GEOMETRY_SHADER, readFile("shaders/flat.gs.glsl").c_str());
    ShaderObject fragmentF("flat.fs.glsl", GL_FRAGMENT_SHADER, readFile("shaders/gouraud.fs.glsl").c_str());
    flat.attachShaderObject(vertexF);
    flat.attachShaderObject(geomF);
    flat.attachShaderObject(fragmentF);
    flat.link();
    
    flat.use();
    glUniform1i(flat.getUniformLoc("diffuseSampler"), 0);
    glUniform1i(flat.getUniformLoc("specularSampler"), 1);
    
    mvpLocationFlat = flat.getUniformLoc("mvp");
    modelViewLocationFlat = flat.getUniformLoc("modelView");
    viewLocationFlat = flat.getUniformLoc("view");
    normalLocationFlat = flat.getUniformLoc("normalMatrix");
}

