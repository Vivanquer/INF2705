#include "scene_tessellation.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "utils.h"
#include "shader_object.h"

#include <iostream>

SceneTessellation::SceneTessellation(bool& isMouseMotionEnabled)
: Scene()
, m_isMouseMotionEnabled(isMouseMotionEnabled)
, m_cameraPosition(0)
, m_cameraOrientation(0)
, m_tessellationShaderProgram("Tessellation")
, m_terrainBuffer()
, m_terrainVao()
, m_terrainVerticesCount(0)
, m_heightmapTexture("../textures/heightmap.png")
, m_grassTexture("../textures/grass.jpg")
, m_sandTexture("../textures/sand.jpg")
, m_snowTexture("../textures/snow.jpg")
, m_viewWireframe(false)
, m_menuVisible(true)
{
    initializeShader();    
    initializeTexture();
    generateMesh();

    // TODO
}

void SceneTessellation::run(Window& w, double dt)
{
    updateInput(w, dt);
    
    drawMenu();    

    m_tessellationShaderProgram.use();
    m_heightmapTexture.use(0);
    m_grassTexture.use(1);
    m_sandTexture.use(2);
    m_snowTexture.use(3);

    glm::mat4 projPersp = getProjectionMatrix(w);
    glm::mat4 view = getCameraFirstPerson();
    glm::mat4 projView = projPersp * view;
    glm::mat4 modelView = view;
    glm::mat4 mvp = projView;
    
    glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(m_modelViewLocation, 1, GL_FALSE, &modelView[0][0]);

    glUniform1i(m_viewWireframeLocation, m_viewWireframe);

    // TODO: To remove, only for debug
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//GL_FILL
    
    m_terrainVao.bind();
    // TODO
    //glDrawArrays(, 0, m_terrainVerticesCount);
}

void SceneTessellation::updateInput(Window& w, double dt)
{
    // Mouse input
    int x = 0, y = 0;
    if (m_isMouseMotionEnabled)
        w.getMouseMotion(x, y);
    const float MOUSE_SENSITIVITY = 0.1;
    float cameraMouvementX = y * MOUSE_SENSITIVITY;
    float cameraMouvementY = x * MOUSE_SENSITIVITY;;
    
    const float KEYBOARD_MOUSE_SENSITIVITY = 1.5f;
    if (w.getKeyHold(Window::Key::UP))
        cameraMouvementX -= KEYBOARD_MOUSE_SENSITIVITY;
    if (w.getKeyHold(Window::Key::DOWN))
        cameraMouvementX += KEYBOARD_MOUSE_SENSITIVITY;
    if (w.getKeyHold(Window::Key::LEFT))
        cameraMouvementY -= KEYBOARD_MOUSE_SENSITIVITY;
    if (w.getKeyHold(Window::Key::RIGHT))
        cameraMouvementY += KEYBOARD_MOUSE_SENSITIVITY;
    
    m_cameraOrientation.y -= cameraMouvementY * dt;
    m_cameraOrientation.x -= cameraMouvementX * dt;

    // Keyboard input
    glm::vec3 positionOffset = glm::vec3(0.0);
    const float SPEED = 10.f;
    if (w.getKeyHold(Window::Key::W))
        positionOffset.z -= SPEED;
    if (w.getKeyHold(Window::Key::S))
        positionOffset.z += SPEED;
    if (w.getKeyHold(Window::Key::A))
        positionOffset.x -= SPEED;
    if (w.getKeyHold(Window::Key::D))
        positionOffset.x += SPEED;
        
    if (w.getKeyHold(Window::Key::Q))
        positionOffset.y -= SPEED;
    if (w.getKeyHold(Window::Key::E))
        positionOffset.y += SPEED;

    positionOffset = glm::rotate(glm::mat4(1.0f), m_cameraOrientation.y, glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(positionOffset, 1);
    m_cameraPosition += positionOffset * glm::vec3(dt);
}

void SceneTessellation::drawMenu()
{
    if (!m_menuVisible) return;
    
    ImGui::Begin("Scene Parameters");    
    ImGui::Checkbox("View wireframe?", (bool*)&m_viewWireframe);
    ImGui::End();
}

void SceneTessellation::generateMesh()
{
    const int N_DIVISIONS = 9;
    const int N_PRIMITIVES = N_DIVISIONS + 1;
    const int N_COMPONENTS = 3;
    const int N_PER_PRIMITIVE = 4;
    const int DATA_SIZE = N_PRIMITIVES * N_PRIMITIVES * N_PER_PRIMITIVE * N_COMPONENTS;
    const GLfloat SIZE = 256.0f;
    const GLfloat FACTOR = SIZE / N_PRIMITIVES;
    const GLfloat OFFSET = -SIZE / 2;
    GLfloat planeData[DATA_SIZE];
    m_terrainVerticesCount = N_PRIMITIVES * N_PRIMITIVES * N_PER_PRIMITIVE;

    for (int i = 0; i < DATA_SIZE;)
    {
        int primitiveIndex = i / (N_PER_PRIMITIVE * N_COMPONENTS);
        int x = primitiveIndex % (N_PRIMITIVES);
        int y = primitiveIndex / (N_PRIMITIVES);

        int X = x + 1;
        int Y = y + 1;

        planeData[i++] = x * FACTOR + OFFSET;
        planeData[i++] = -1.0f;
        planeData[i++] = y * FACTOR + OFFSET;

        planeData[i++] = x * FACTOR + OFFSET;
        planeData[i++] = -1.0f;
        planeData[i++] = Y * FACTOR + OFFSET;

        planeData[i++] = X * FACTOR + OFFSET;
        planeData[i++] = -1.0f;
        planeData[i++] = Y * FACTOR + OFFSET;

        planeData[i++] = X * FACTOR + OFFSET;
        planeData[i++] = -1.0f;
        planeData[i++] = y * FACTOR + OFFSET;
    }

    m_terrainBuffer.allocate(GL_ARRAY_BUFFER, sizeof(planeData), planeData, GL_STATIC_DRAW);
    m_terrainVao.specifyAttribute(m_terrainBuffer, 0, 3, 0, 0);
}

void SceneTessellation::initializeShader()
{
    ShaderObject vertex("tessellation.vs.glsl", GL_VERTEX_SHADER, readFile("shaders/tessellation.vs.glsl").c_str());
    ShaderObject tessControl("tessellation.tcs.glsl", GL_TESS_CONTROL_SHADER, readFile("shaders/tessellation.tcs.glsl").c_str());
    ShaderObject tessEval("tessellation.tes.glsl", GL_TESS_EVALUATION_SHADER, readFile("shaders/tessellation.tes.glsl").c_str());
    ShaderObject geometry("tessellation.gs.glsl",GL_GEOMETRY_SHADER, readFile("shaders/tessellation.gs.glsl").c_str());
    ShaderObject fragment("tessellation.fs.glsl",GL_FRAGMENT_SHADER, readFile("shaders/tessellation.fs.glsl").c_str());
    m_tessellationShaderProgram.attachShaderObject(vertex);
    m_tessellationShaderProgram.attachShaderObject(tessControl);
    m_tessellationShaderProgram.attachShaderObject(tessEval);
    m_tessellationShaderProgram.attachShaderObject(geometry);
    m_tessellationShaderProgram.attachShaderObject(fragment);
    m_tessellationShaderProgram.link();
    
    m_tessellationShaderProgram.use();
    glUniform1i(m_tessellationShaderProgram.getUniformLoc("heighmapSampler"), 0);
    glUniform1i(m_tessellationShaderProgram.getUniformLoc("groundSampler"), 1);
    glUniform1i(m_tessellationShaderProgram.getUniformLoc("sandSampler"), 2);
    glUniform1i(m_tessellationShaderProgram.getUniformLoc("snowSampler"), 3);

    m_mvpLocation = m_tessellationShaderProgram.getUniformLoc("mvp");
    m_modelViewLocation = m_tessellationShaderProgram.getUniformLoc("modelView");
    m_viewWireframeLocation = m_tessellationShaderProgram.getUniformLoc("viewWireframe");
}

void SceneTessellation::initializeTexture()
{
    m_heightmapTexture.setWrap(GL_CLAMP_TO_EDGE);
	m_heightmapTexture.setFiltering(GL_LINEAR);
    
    m_grassTexture.setWrap(GL_REPEAT);
	m_grassTexture.setFiltering(GL_LINEAR);
	m_grassTexture.enableMipmap();
	
    m_sandTexture.setWrap(GL_REPEAT);
	m_sandTexture.setFiltering(GL_LINEAR);
	m_sandTexture.enableMipmap();
	
    m_snowTexture.setWrap(GL_REPEAT);
	m_snowTexture.setFiltering(GL_LINEAR);
	m_snowTexture.enableMipmap();
}


