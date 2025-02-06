#ifndef SCENE_ATTRACTION_H
#define SCENE_ATTRACTION_H

#include "scene.h"

#include <glm/glm.hpp>

#include "model.h"
#include "texture.h"

class SceneAttraction : public Scene
{
public:
    SceneAttraction(Resources& res, bool& isMouseMotionEnabled);
    ~SceneAttraction();

    virtual void run(Window& w, double dt);
    
private:
    void updateInput(Window& w, double dt);

    glm::mat4 getCameraFirstPerson();
    glm::mat4 getCameraThirdPerson();
    
    glm::mat4 getProjectionMatrix(Window& w);
    
private:
    const char* const CAMERA_MODE_NAMES[3] = {
        "First person",
        "Third person",
        "Monkey",
    };
    const int N_CAMERA_MODE_NAMES = sizeof(CAMERA_MODE_NAMES) / sizeof(CAMERA_MODE_NAMES[0]);

    bool& m_isMouseMotionEnabled;
    int m_cameraMode;
    bool m_isOrtho;

    glm::vec3 m_cameraPosition;
    glm::vec2 m_cameraOrientation;
    
    BufferObject m_groundBuffer;
    BufferObject m_groundIndicesBuffer;
    VertexArrayObject m_groundVao;
    DrawElementsCommand m_groundDraw;
    
    float m_largePlatformAngle;
    float m_smallPlatformAngle[3];
    float m_cupsAngles[3][4];    

    Model m_suzanne;    
    Model m_cup;
    Model m_cupPlate;
    Model m_smallPlatform;
    Model m_largePlatform;
    Model m_cube;
    
    Texture2D m_groundTexture;
    Texture2D m_suzanneTexture;
    Texture2D m_cupTextureAtlas;
    Texture2D m_smallPlatformTexture;
    Texture2D m_largePlatformTexture;
};

#endif // SCENE_ATTRACTION_H
