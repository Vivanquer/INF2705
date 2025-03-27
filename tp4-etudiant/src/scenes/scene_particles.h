#ifndef SCENE_PARTICLES_H
#define SCENE_PARTICLES_H

#include "scene.h"

#include <glm/glm.hpp>

#include "shader_program.h"
#include "texture.h"


struct Particle
{
    //GLint type;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;
    glm::vec2 size;
    GLfloat timeToLive;
};


class SceneParticles : public Scene
{
public:
    SceneParticles(bool& isMouseMotionEnabled);
    virtual ~SceneParticles();

    virtual void run(Window& w, double dt);
    
private:
    void updateInput(Window& w, double dt);
    void initializeShader();
    void initializeTexture();
    void drawMenu();
    
    glm::mat4 getCameraThirdPerson(float dist = 4.0f);    
    glm::mat4 getProjectionMatrix(Window& w);
    
private:
    bool& m_isMouseMotionEnabled;

    glm::vec2 m_cameraOrientation;

    float m_totalTime;
    float m_cumulativeTime;

    GLuint m_tfo, m_vao, m_vbo[2];
    unsigned int m_nParticles;
    unsigned int m_nMaxParticles;
    
    ShaderProgram m_transformFeedbackShaderProgram;
    GLint m_timeLocationTransformFeedback;
    GLint m_dtLocationTransformFeedback;
    
    ShaderProgram m_particleShaderProgram;
    GLint m_modelViewLocationParticle;
    GLint m_projectionLocationParticle;
    
    Texture2D m_flameTexture;
    
    // IMGUI VARIABLE
    bool m_menuVisible;
};

#endif // SCENE_PARTICLES_H
