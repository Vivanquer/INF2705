#include "scene_particles.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "utils.h"
#include "shader_object.h"

#include <iostream>



static const unsigned int MAX_N_PARTICULES = 1000;
static Particle particles[MAX_N_PARTICULES] = { {{0,0,0},{0,0,0},{0,0,0,0}, {0,0},0} };

SceneParticles::SceneParticles(bool& isMouseMotionEnabled)
: Scene()
, m_isMouseMotionEnabled(isMouseMotionEnabled)
, m_cameraOrientation(0)
, m_totalTime(0.0f)
, m_cumulativeTime(0.0f)
, m_tfo(0)
, m_vao(0)
, m_vbo{0, 0}
, m_nParticles(1)
, m_nMaxParticles(MAX_N_PARTICULES)
, m_transformFeedbackShaderProgram("TransformFeedback")
, m_timeLocationTransformFeedback(-1)
, m_dtLocationTransformFeedback(-1)
, m_particleShaderProgram("ParticleShader")
, m_modelViewLocationParticle(-1)
, m_projectionLocationParticle(-1)
, m_flameTexture("../textures/flame.png")
, m_menuVisible(true)
{
    initializeShader();
    initializeTexture();

    glEnable(GL_PROGRAM_POINT_SIZE);
    
    // TODO
}

SceneParticles::~SceneParticles()
{
    // TODO
}

void SceneParticles::run(Window& w, double dt)
{
    updateInput(w, dt);
    
    drawMenu();
    
    glm::mat4 view = getCameraThirdPerson(2.5);
    glm::mat4 projPersp = getProjectionMatrix(w);
    glm::mat4 modelView = view;

    m_totalTime += dt;
    m_cumulativeTime += dt;
    if (dt == 0.0f)
        m_nParticles = 1;

    m_transformFeedbackShaderProgram.use();
    glUniform1f(m_timeLocationTransformFeedback, m_totalTime);
    glUniform1f(m_dtLocationTransformFeedback, (float)dt);
    
    // TODO: buffer binding
    // TODO: update particles
    // TODO: swap buffers

    m_particleShaderProgram.use();
    m_flameTexture.use(0);
    
    glUniformMatrix4fv(m_modelViewLocationParticle, 1, GL_FALSE, &modelView[0][0]);
    glUniformMatrix4fv(m_projectionLocationParticle, 1, GL_FALSE, &projPersp[0][0]);

    // TODO: buffer binding
    // TODO: Draw particles without depth write and with blending

    if (m_cumulativeTime > 1.0f / 60.0f)
    {
        m_cumulativeTime = 0.0f;
        if (++m_nParticles > m_nMaxParticles)
            m_nParticles = m_nMaxParticles;
    }
}

void SceneParticles::updateInput(Window& w, double dt)
{        
    int x = 0, y = 0;
    if (m_isMouseMotionEnabled)
        w.getMouseMotion(x, y);
    const float MOUSE_SENSITIVITY = 0.1;
    float cameraMouvementX = y * MOUSE_SENSITIVITY;
    float cameraMouvementY = x * MOUSE_SENSITIVITY;
    
    const float KEYBOARD_MOUSE_SENSITIVITY = 1.5f;
    if (w.getKeyHold(Window::Key::UP))
        cameraMouvementX += KEYBOARD_MOUSE_SENSITIVITY;
    if (w.getKeyHold(Window::Key::DOWN))
        cameraMouvementX -= KEYBOARD_MOUSE_SENSITIVITY;
    if (w.getKeyHold(Window::Key::LEFT))
        cameraMouvementY += KEYBOARD_MOUSE_SENSITIVITY;
    if (w.getKeyHold(Window::Key::RIGHT))
        cameraMouvementY -= KEYBOARD_MOUSE_SENSITIVITY;
    
    m_cameraOrientation.y -= cameraMouvementY * dt;
    m_cameraOrientation.x -= cameraMouvementX * dt;
}

void SceneParticles::drawMenu()
{
    if (!m_menuVisible) return;

    ImGui::Begin("Scene Parameters");
    ImGui::End();
}


void SceneParticles::initializeShader()
{
    // Particule shader
    {
        std::string vertexCode = readFile("shaders/particle.vs.glsl");
        std::string geometryCode = readFile("shaders/particle.gs.glsl");
        std::string fragmentCode = readFile("shaders/particle.fs.glsl");

        ShaderObject vertex("particule.vs.glsl", GL_VERTEX_SHADER, vertexCode.c_str());
        ShaderObject geometry("particule.gs.glsl", GL_GEOMETRY_SHADER, geometryCode.c_str());
        ShaderObject fragment("particule.fs.glsl",GL_FRAGMENT_SHADER, fragmentCode.c_str());
        m_particleShaderProgram.attachShaderObject(vertex);
        m_particleShaderProgram.attachShaderObject(geometry);
        m_particleShaderProgram.attachShaderObject(fragment);
        m_particleShaderProgram.link();

        m_modelViewLocationParticle = m_particleShaderProgram.getUniformLoc("modelView");
        m_projectionLocationParticle = m_particleShaderProgram.getUniformLoc("projection");
    }
    
    // Transform feedback shader
    {
        std::string vertexCode = readFile("shaders/transformFeedback.vs.glsl");

        ShaderObject vertex("transformFeedback.vs.glsl", GL_VERTEX_SHADER, vertexCode.c_str());
        m_transformFeedbackShaderProgram.attachShaderObject(vertex);

        // TODO
        
        m_transformFeedbackShaderProgram.link();

        m_timeLocationTransformFeedback = m_transformFeedbackShaderProgram.getUniformLoc("time");
        m_dtLocationTransformFeedback = m_transformFeedbackShaderProgram.getUniformLoc("dt");
    }
}

void SceneParticles::initializeTexture()
{
    m_flameTexture.setFiltering(GL_LINEAR);
    m_flameTexture.setWrap(GL_CLAMP_TO_EDGE);
}

