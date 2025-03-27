#ifndef SCENE_TESSELLATION_H
#define SCENE_TESSELLATION_H

#include "scene.h"

#include <glm/glm.hpp>

#include "buffer_object.h"
#include "vertex_array_object.h"
#include "draw_commands.h"
#include "shader_program.h"
#include "texture.h"


class SceneTessellation : public Scene
{
public:
    SceneTessellation(bool& isMouseMotionEnabled);

    virtual void run(Window& w, double dt);
    
private:
    void updateInput(Window& w, double dt);
    void generateMesh();
    void initializeShader();
    void initializeTexture();
    void drawMenu();
    
    glm::mat4 getCameraFirstPerson();
    glm::mat4 getProjectionMatrix(Window& w);
    
private:
    bool& m_isMouseMotionEnabled;

    glm::vec3 m_cameraPosition;
    glm::vec2 m_cameraOrientation;
    
    ShaderProgram m_tessellationShaderProgram;
    GLint m_mvpLocation;
    GLint m_modelViewLocation;
    GLint m_viewWireframeLocation;
    
    BufferObject m_terrainBuffer;
    VertexArrayObject m_terrainVao;
    GLsizei m_terrainVerticesCount;

    Texture2D m_heightmapTexture;
    Texture2D m_grassTexture;
    Texture2D m_sandTexture;
    Texture2D m_snowTexture;

    // IMGUI VARIABLE
    bool m_viewWireframe;
    bool m_menuVisible;
};

#endif // SCENE_TESSELLATION_H
