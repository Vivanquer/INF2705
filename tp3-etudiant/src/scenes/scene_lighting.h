#ifndef SCENE_LIGHTING_H
#define SCENE_LIGHTING_H

#include "scene.h"

#include <glm/glm.hpp>

#include "model.h"
#include "texture.h"
#include "uniform_buffer.h"



struct Material
{
    glm::vec4 emission; // vec3, but padded
    glm::vec4 ambient;  // vec3, but padded
    glm::vec4 diffuse;  // vec3, but padded
    glm::vec3 specular;
    GLfloat shininess;
};

struct UniversalLight
{
    glm::vec4 ambient;  // vec3, but padded
    glm::vec4 diffuse;  // vec3, but padded
    glm::vec4 specular; // vec3, but padded
    glm::vec4 position; // vec3, but padded
    glm::vec4 spotDirection; // vec3, but padded
};

struct LightModel
{
    glm::vec3 lightModelAmbient;
    GLuint useBlinn;
    GLuint useSpotlight;
    GLuint useDirect3D;
    GLfloat spotExponent;
    GLfloat spotOpeningAngle;
};


class SceneLighting : public Scene
{
public:
    SceneLighting(Resources& res, bool& isMouseMotionEnabled);

    virtual void run(Window& w, double dt);
    
private:
    void updateInput(Window& w, double dt);
    
    void drawMenu();
    
    glm::mat4 getCameraThirdPerson(float dist = 4.0f);    
    glm::mat4 getProjectionMatrix(Window& w);
    
private:
    bool& m_isMouseMotionEnabled;

    glm::vec2 m_cameraOrientation;

    Model m_suzanne;
    Model m_sphere;
    Model m_cube;
    Model m_spotlight;
    
    Texture2D m_whiteTexture;
    Texture2D m_diffuseMapTexture;
    Texture2D m_specularMapTexture;
    
    LightModel m_lightModel;
    Material m_material;
    UniversalLight m_lights[3];
    UniformBuffer m_lightingData;

    glm::vec2 orientation[3];

    // IMGUI VARIABLE
    int m_currentModel;
    int m_currentShading;
    bool m_menuVisible;
};

#endif // SCENE_LIGHTING_H
