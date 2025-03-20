#ifndef SCENE_STENCIL_H
#define SCENE_STENCIL_H

#include "scene.h"

#include <glm/glm.hpp>

#include "model.h"
#include "texture.h"


class SceneStencil : public Scene
{
public:
    SceneStencil(Resources& resources, bool& isMouseMotionEnabled);
    virtual ~SceneStencil();

    virtual void run(Window& w, double dt);

private:
    void updateInput(Window& w, double dt);
    
    glm::mat4 getCameraFirstPerson();
    glm::mat4 getProjectionMatrix(Window& w);

private:
    static GLfloat groundData[5*4];
    static GLubyte indexes[6];

    bool& m_isMouseMotionEnabled;
    glm::vec3 m_cameraPosition;
    glm::vec2 m_cameraOrientation;
    
    BufferObject m_groundBuffer;
    BufferObject m_groundIndicesBuffer;
    VertexArrayObject m_groundVao;
    DrawElementsCommand m_groundDraw;
    
    Model m_suzanne;
    Model m_rock;
    Model m_glass;
    
    Texture2D m_groundTexture;
    Texture2D m_suzanneTexture;
    Texture2D m_suzanneWhiteTexture;
    Texture2D m_rockTexture;
    Texture2D m_glassTexture;
    Texture2D m_whiteGridTexture;
};


#endif // SCENE_STENCIL_H
