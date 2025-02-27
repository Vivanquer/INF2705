#include "scene_attraction.h"

#include <iostream>
#include "imgui/imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utils.h"

// TODO - coordonnées de texture
const GLfloat groundData[] = {
    // Position (x, y, z) et coordonnées texture (u, v)
    -45.f, 0.0f, -45.f,  0.0f, 0.0f,
     45.f, 0.0f, -45.f,  1.0f, 0.0f,
    -45.f, 0.0f,  45.f,  0.0f, 1.0f,
     45.f, 0.0f,  45.f,  1.0f, 1.0f,
};

const GLubyte indexes[] = {
    2, 3, 0,
    3, 1, 0
};


SceneAttraction::SceneAttraction(Resources& res, bool& isMouseMotionEnabled)
: Scene(res)
, m_isMouseMotionEnabled(isMouseMotionEnabled)
, m_cameraMode(0)
, m_isOrtho(false)
, m_cameraPosition(0.0f, 5.0f, 0.0f)
, m_cameraOrientation(0.0f, 0.0f)

, m_groundBuffer(GL_ARRAY_BUFFER, sizeof(groundData), groundData, GL_STATIC_DRAW)
, m_groundIndicesBuffer(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW)
, m_groundVao()
, m_groundDraw(m_groundVao, 6)

, m_largePlatformAngle(0.0f)
, m_smallPlatformAngle{0.0f}
, m_cupsAngles{0.0f}

, m_suzanne("../models/suzanne.obj")
, m_cup("../models/cup.obj")
, m_cupPlate("../models/plate.obj")
, m_smallPlatform("../models/smallPlatform.obj")
, m_largePlatform("../models/largePlatform.obj")
, m_cube("../models/cube.obj")

, m_groundTexture("../textures/grassSeamless.jpg")
, m_suzanneTexture("../textures/suzanneTextureShade.png")
, m_cupTextureAtlas("../textures/cupTextureAtlas.png")
, m_smallPlatformTexture("../textures/smallPlatform.png")
, m_largePlatformTexture("../textures/largePlatform.png")
{
   // Spécifier les attributs du VAO pour le sol :
    // Format : (position: 3 floats, texture: 2 floats)
    m_groundVao.bind();
    m_groundBuffer.bind();
    m_groundIndicesBuffer.bind();
    
    GLsizei stride = 5;
    // Attribut 0 : position (3 floats)
    m_groundVao.specifyAttribute(m_groundBuffer, 0, 3, stride, 0);
    // Attribut 1 : coordonnées de texture (2 floats)
    m_groundVao.specifyAttribute(m_groundBuffer, 1, 2, stride, 3);
    std::cout << "VAO du sol configuré" << std::endl;
    m_groundVao.unbind();
    
    // Initialisation des textures (choix de filtres et mode de wrap)
    m_groundTexture.setFiltering(GL_LINEAR);
    m_groundTexture.setWrap(GL_REPEAT);
    m_groundTexture.enableMipmap();
    
    m_suzanneTexture.setFiltering(GL_LINEAR);
    m_suzanneTexture.setWrap(GL_CLAMP_TO_EDGE);
    
    m_cupTextureAtlas.setFiltering(GL_LINEAR);
    m_cupTextureAtlas.setWrap(GL_CLAMP_TO_EDGE);
    
    m_smallPlatformTexture.setFiltering(GL_LINEAR);
    m_smallPlatformTexture.setWrap(GL_CLAMP_TO_EDGE);
    
    m_largePlatformTexture.setFiltering(GL_LINEAR);
    m_largePlatformTexture.setWrap(GL_CLAMP_TO_EDGE);
}

SceneAttraction::~SceneAttraction()
{
}

void SceneAttraction::run(Window& w, double dt)
{    
    ImGui::Begin("Scene Parameters");
    ImGui::Combo("Camera mode", &m_cameraMode, CAMERA_MODE_NAMES, N_CAMERA_MODE_NAMES);
    ImGui::Checkbox("Orthographic camera?", &m_isOrtho);
    ImGui::End();
    
    m_resources.texture.use();

    // m_resources.mvpLocationTexture.use();
    updateInput(w, dt);    
    m_largePlatformAngle += 0.5 * dt;
    for (int i = 0; i < 3; i++)
    {
        m_smallPlatformAngle[i] += 0.5 * dt;
        for (int j = 0; j < 4; j++)
            m_cupsAngles[i][j] += (0.5 + j * 0.5f) * dt;
    }
    glm::mat4 model, proj, view, mvp, mvpArraySmallPlat[3];
    proj = getProjectionMatrix(w);
    if (m_cameraMode == 0 || m_cameraMode == 2)
        view = getCameraFirstPerson();
    else
        view = getCameraThirdPerson();


    glm::mat4 pv = proj * view;
    mvp = pv * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));
    // mvp = pv;
    // TODO - dessin de la scène
    //le grass
    m_groundTexture.use();
    glUniformMatrix4fv(m_resources.mvpLocationTexture, 1, GL_FALSE, &mvp[0][0]);
    m_groundDraw.draw();

    //grande plateforme
    mvp = pv * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.1f, 0.0f));
    m_largePlatformTexture.use();
    glUniformMatrix4fv(m_resources.mvpLocationTexture, 1, GL_FALSE, &mvp[0][0]);
    m_largePlatform.draw();

    //petite plateforme
    const int N_SMALLPLATFORM = 3;
    const float RADIUS = 15.0f;
    const float ANGLE_STEP = glm::radians(120.0f);  

    m_smallPlatformTexture.use();

    for (int i = 0; i < N_SMALLPLATFORM; i++)
    {
        float angle = i * ANGLE_STEP;  
        glm::vec3 position = glm::vec3(RADIUS * cos(angle), 0.0f, RADIUS * sin(angle));  // Compute position on circle

        glm::mat4 model = glm::translate(glm::mat4(1.0f), position);  // Move to correct position
        model = glm::rotate(model, m_smallPlatformAngle[i], glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate around Y

        mvpArraySmallPlat[i] = pv * model;  
        glUniformMatrix4fv(m_resources.mvpLocationTexture, 1, GL_FALSE, &mvpArraySmallPlat[i][0][0]);
        
        m_smallPlatform.draw();
    }
   
    m_resources.colorUniform.use();

    const int N_CUP = 4;  
    const float PLATFORM_RADIUS = 15.0f;  
    const float CUP_RADIUS = 6.0f;  
    const float ANGLE_STEP_PLATFORM = glm::radians(120.0f);  
    const float ANGLE_STEP_CUP = glm::radians(90.0f);  

    glm::mat4 mvpArrayCups[3][4];
    glm::mat4 mvpArrayPlates[3][4];

    m_smallPlatformTexture.use();

    for (int i = 0; i < N_SMALLPLATFORM; i++)
    {
        float angle = i * ANGLE_STEP_PLATFORM;
        glm::vec3 platformPos = glm::vec3(PLATFORM_RADIUS * cos(angle), 0.0f, PLATFORM_RADIUS * sin(angle));

        glm::mat4 platformModel = glm::translate(glm::mat4(1.0f), platformPos);
        platformModel = glm::rotate(platformModel, m_smallPlatformAngle[i], glm::vec3(0.0f, 1.0f, 0.0f));

        mvpArraySmallPlat[i] = pv * platformModel;
        glUniformMatrix4fv(m_resources.mvpLocationTexture, 1, GL_FALSE, &mvpArraySmallPlat[i][0][0]);
        m_smallPlatform.draw();

        m_cupTextureAtlas.use();

        for (int j = 0; j < N_CUP; j++)
        {
            float cupAngle = j * ANGLE_STEP_CUP;
            glm::vec3 cupPos = glm::vec3(CUP_RADIUS * cos(cupAngle), 0.12f, CUP_RADIUS * sin(cupAngle));

            glm::mat4 cupModel = glm::translate(platformModel, cupPos);  
            cupModel = glm::rotate(cupModel, m_cupsAngles[i][j], glm::vec3(0.0f, 1.0f, 0.0f));

            mvpArrayCups[i][j] = pv * cupModel;
            glUniformMatrix4fv(m_resources.mvpLocationColorUniform, 1, GL_FALSE, &mvpArrayCups[i][j][0][0]);
            m_cup.draw();

            m_cupTextureAtlas.use();
            glm::mat4 plateModel = glm::translate(platformModel, glm::vec3(CUP_RADIUS * cos(cupAngle), 0.0f, CUP_RADIUS * sin(cupAngle)));
            
            mvpArrayPlates[i][j] = pv * plateModel;
            glUniformMatrix4fv(m_resources.mvpLocationColorUniform, 1, GL_FALSE, &mvpArrayPlates[i][j][0][0]);
            m_cupPlate.draw();
        }
    }

    glUniformMatrix4fv(m_resources.mvpLocationColorUniform, 1, GL_FALSE, &mvp[0][0]);
    // m_resources.texture.draw();
    // Debut de code pour le dessin des groupes de tasses (et obtenir la position du singe)
    model = glm::mat4(1.0f);
    mvp = proj * view * model;
    
    glm::vec3 monkeyPos(0.0f);
    float monkeyHeading = 0.0f;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Calculez la matrice de transformation pour chaque tasse...
            glm::mat4 cupModelMat = glm::mat4(1.0f);
            // Exemple : si c'est la première tasse, récupérez sa position pour la caméra "Monkey"
            if (i == 0 && j == 0)
            {
                monkeyPos = glm::vec3(cupModelMat[3]);
                monkeyPos.y = 1.3f;
                monkeyHeading = atan2(cupModelMat[2].x, cupModelMat[0].x);
            }
        }
    }    
    // Ajustement de la caméra en mode "Monkey"
    if (m_cameraMode == 2)
    {
        m_cameraPosition = monkeyPos;
        m_cameraPosition.y = 3.8f;
        m_cameraOrientation.y = monkeyHeading;
    }

    
}

void SceneAttraction::updateInput(Window& w, double dt)
{
    // Mouse input
    int x = 0, y = 0;
    if (m_isMouseMotionEnabled)
        w.getMouseMotion(x, y);
    const float MOUSE_SENSITIVITY = 0.1;
    float cameraMouvementX = y * MOUSE_SENSITIVITY;
    float cameraMouvementY = x * MOUSE_SENSITIVITY;
    
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
        positionOffset.x -= SPEED;
    if (w.getKeyHold(Window::Key::S))
        positionOffset.x += SPEED;
    if (w.getKeyHold(Window::Key::A))
        positionOffset.z += SPEED;
    if (w.getKeyHold(Window::Key::D))
        positionOffset.z -= SPEED;
        
    if (w.getKeyHold(Window::Key::Q))
        positionOffset.y -= SPEED;
    if (w.getKeyHold(Window::Key::E))
        positionOffset.y += SPEED;

    positionOffset = glm::rotate(glm::mat4(1.0f), m_cameraOrientation.y, glm::vec3(0.0, 1.0, 0.0)) * glm::vec4(positionOffset, 1);
    m_cameraPosition += positionOffset * glm::vec3(dt);
}

glm::mat4 SceneAttraction::getCameraFirstPerson()
{
    // TODO
    glm::vec3 front;
    front.x = cos(m_cameraOrientation.x) * cos(m_cameraOrientation.y);
    front.y = sin(m_cameraOrientation.x);
    front.z = cos(m_cameraOrientation.x) * sin(m_cameraOrientation.y);
    front = glm::normalize(front);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(front, up));
    glm::vec3 cameraUp = glm::normalize(glm::cross(right, front));
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0] = glm::vec4(right, 0.0f);
    rotation[1] = glm::vec4(cameraUp, 0.0f);
    rotation[2] = glm::vec4(-front, 0.0f);
    glm::mat4 translation = glm::mat4(1.0f);
    translation = glm::translate(translation, -m_cameraPosition);
    return rotation * translation;
}


glm::mat4 SceneAttraction::getCameraThirdPerson()
{
    // TODO
    glm::vec3 offset(0.0f, 5.0f, 15.0f);
    glm::vec3 cameraPos = m_cameraPosition + offset;
    glm::vec3 front = glm::normalize(m_cameraPosition - cameraPos); 
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right = glm::normalize(glm::cross(up, front)); 
    glm::vec3 cameraUp = glm::normalize(glm::cross(front, right)); 
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0] = glm::vec4(right, 0.0f);
    rotation[1] = glm::vec4(cameraUp, 0.0f);
    rotation[2] = glm::vec4(-front, 0.0f);
    glm::mat4 translation = glm::mat4(1.0f);
    translation = glm::translate(translation, -cameraPos);
    return rotation * translation;
}

glm::mat4 SceneAttraction::getProjectionMatrix(Window& w)
{
    // TODO
    const float SCREEN_SIZE_ORTHO = 10.0f;
    glm::mat4 proj;
    if (m_isOrtho)
    {
        proj = glm::ortho(-SCREEN_SIZE_ORTHO, SCREEN_SIZE_ORTHO, -SCREEN_SIZE_ORTHO, SCREEN_SIZE_ORTHO, 0.1f, 300.0f);
    }
    else
    {
        // Remplacez getAspectRatio() par le calcul manuel
        float aspect = static_cast<float>(w.getWidth()) / static_cast<float>(w.getHeight());   
        proj = glm::perspective(glm::radians(75.0f), aspect, 0.1f, 300.0f);
    }
    return proj;
}

