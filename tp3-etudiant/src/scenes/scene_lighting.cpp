#include "scene_lighting.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

#include "utils.h"

#include <iostream>

SceneLighting::SceneLighting(Resources& res, bool& isMouseMotionEnabled)
: Scene(res)
, m_isMouseMotionEnabled(isMouseMotionEnabled)
, m_cameraOrientation(0)

, m_suzanne("../models/suzanne.obj")
, m_sphere("../models/icosphere.obj")
, m_cube("../models/cube.obj")
, m_spotlight("../models/spotlight.obj")

, m_whiteTexture("../textures/white.png")
, m_diffuseMapTexture("../textures/metal_0029_color_1k.jpg")
, m_specularMapTexture("../textures/metal_0029_metallic_1k.jpg")

, m_lightingData(nullptr, sizeof(m_lightModel) + sizeof(m_material) + sizeof(m_lights))

, m_currentModel(0)
, m_currentShading(2)
, m_menuVisible(true)
{
    m_whiteTexture.setFiltering(GL_LINEAR);
    m_whiteTexture.setWrap(GL_CLAMP_TO_EDGE);
   
    m_diffuseMapTexture.setFiltering(GL_LINEAR);
    m_diffuseMapTexture.setWrap(GL_CLAMP_TO_EDGE);
   
    m_specularMapTexture.setFiltering(GL_LINEAR);
    m_specularMapTexture.setWrap(GL_CLAMP_TO_EDGE);
    
    m_lightModel =
    {
        glm::vec3(0.2f),
        false,
        false,
        false,
        1.0f,
        20.0f
    };

    m_material =
    {
        {0.0f, 0.0f, 0.0f, 0.0f},
        {0.8f, 0.8f, 0.8f, 0.0f},
        {0.8f, 0.8f, 0.8f, 0.0f},
        {1.0f, 1.0f, 1.0f},
        100.0f
    };

    m_lights[0] =
    {
        {0.1f, 0.0f, 0.0f, 0.0f},
        {1.0f, 0.2f, 0.2f, 0.0f},
        {0.5f, 0.1f, 0.1f, 0.0f},
        {1.5f, 2.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f}
    };    
    m_lights[1] =
    {
        {0.0f, 0.1f, 0.0f, 0.0f},
        {0.2f, 1.0f, 0.2f, 0.0f},
        {0.1f, 0.5f, 0.1f, 0.0f},
        {-1.5f, 1.0f, 1.5f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f}
    };
    m_lights[2] =
    {
        {0.0f, 0.0f, 0.1f, 0.0f},
        {0.2f, 0.2f, 1.0f, 0.0f},
        {0.1f, 0.1f, 0.5f, 0.0f},
        {0.0f, 1.0f, -2.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 0.0f}
    };

    orientation[0] = glm::vec2(45.0f, 55.0f);
    orientation[1] = glm::vec2(45.0f, -45.0f);
    orientation[2] = glm::vec2(45.0f, 180.0f);

    m_resources.phong.setUniformBlockBinding("LightingBlock", 0);
    m_lightingData.setBindingIndex(0);
}

void SceneLighting::run(Window& w, double dt)
{
    updateInput(w, dt);
    
    drawMenu();

    GLintptr offset = 0;
    m_lightingData.updateData(&m_material  , offset, sizeof(m_material));   offset += sizeof(m_material);
    m_lightingData.updateData(m_lights     , offset, sizeof(m_lights));     offset += sizeof(m_lights);
    m_lightingData.updateData(&m_lightModel, offset, sizeof(m_lightModel)); offset += sizeof(m_lightModel);
    
    glm::mat4 projPersp = getProjectionMatrix(w);
    glm::mat4 view = getCameraThirdPerson();

    glm::mat4 mvp;
    glm::mat4 projView = projPersp * view;
    glm::mat4 modelView;

    GLint mvpMatrixLocation = -1;
    GLint viewMatrixLocation = -1;
    GLint modelViewMatrixLocation = -1;
    GLint normalMatrixLocation = -1;
    
    switch (m_currentShading)
    {
    case 0: 
        m_resources.flat.use();
        viewMatrixLocation = m_resources.viewLocationFlat;
        mvpMatrixLocation = m_resources.mvpLocationFlat;
        modelViewMatrixLocation = m_resources.modelViewLocationFlat;
        normalMatrixLocation = m_resources.normalLocationFlat;
        break;
    case 1:
        m_resources.gouraud.use();
        viewMatrixLocation = m_resources.viewLocationGouraud;
        mvpMatrixLocation = m_resources.mvpLocationGouraud;
        modelViewMatrixLocation = m_resources.modelViewLocationGouraud;
        normalMatrixLocation = m_resources.normalLocationGouraud;
        break;
    case 2: 
        m_resources.phong.use();
        viewMatrixLocation = m_resources.viewLocationPhong;
        mvpMatrixLocation = m_resources.mvpLocationPhong;
        modelViewMatrixLocation =  m_resources.modelViewLocationPhong;
        normalMatrixLocation = m_resources.normalLocationPhong;
        break;
    }
    m_diffuseMapTexture.use(0);
    m_specularMapTexture.use(1);

    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &view[0][0]);
    glm::mat4 sphereModel = glm::mat4(1.0f);
    mvp = projView * sphereModel;
    modelView = view * sphereModel;
    glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvp[0][0]);
    glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, &modelView[0][0]);
    glUniformMatrix3fv(normalMatrixLocation, 1, GL_TRUE, glm::value_ptr(glm::inverse(glm::mat3(modelView))));

    switch (m_currentModel)
    {
    case 0: m_sphere.draw(); break;
    case 1: m_cube.draw(); break;
    case 2: m_suzanne.draw(); break;
    }

    m_whiteTexture.use(0);
    m_whiteTexture.use(1);
    for (size_t i = 0; i < 3; ++i)
    {
        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::translate(lightModel, glm::vec3(m_lights[i].position));
        lightModel = glm::rotate(lightModel, glm::radians(orientation[i].y), glm::vec3(0.0f, 1.0f, 0.0f));
        lightModel = glm::rotate(lightModel, glm::radians(orientation[i].x), glm::vec3(1.0f, 0.0f, 0.0f));
        m_lights[i].spotDirection = lightModel * glm::vec4(0, -1, 0, 0);

        mvp = projView * lightModel;
        modelView = view * lightModel;
        glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, &mvp[0][0]);
        glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, &modelView[0][0]);
        glUniformMatrix3fv(normalMatrixLocation, 1, GL_TRUE, glm::value_ptr(glm::inverse(glm::mat3(modelView))));

        Material lightMaterial =
        {
            m_lights[i].diffuse,
            glm::vec4(0.0f),
            glm::vec4(0.0f),
            glm::vec3(0.0f),
            1.0f
        };
        m_lightingData.updateData(&lightMaterial, 0, sizeof(lightMaterial));
        m_spotlight.draw();
    }
}

void SceneLighting::updateInput(Window& w, double dt)
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

void SceneLighting::drawMenu()
{
    if (!m_menuVisible) return;
    const char* modelList[] = { "Sphere", "Cube", "Monkey" };
    const char* shadingList[] = { "Flat", "Gouraud", "Phong" };

    ImGui::Begin("Scene Parameters");

    ImGui::Combo("Model", &m_currentModel, modelList, sizeof(modelList) / sizeof(modelList[0]));
    ImGui::SeparatorText("Material");
    ImGui::ColorEdit3("Emission##m", &m_material.emission[0]);
    ImGui::ColorEdit3("Ambient##m", &m_material.ambient[0]);
    ImGui::ColorEdit3("Diffuse##m", &m_material.diffuse[0]);
    ImGui::ColorEdit3("Specular##m", &m_material.specular[0]);
    ImGui::DragFloat("Shininess##m", &m_material.shininess, 1.0f, 0.0f, 1000.0f);

    ImGui::SeparatorText("Light Model");
    ImGui::Combo("Shading", &m_currentShading, shadingList, sizeof(shadingList) / sizeof(shadingList[0]));
    ImGui::ColorEdit3("Global ambient", &m_lightModel.lightModelAmbient[0]);
    ImGui::Checkbox("Use blinn?", (bool*)&m_lightModel.useBlinn);
    ImGui::Checkbox("Use spotlight?", (bool*)&m_lightModel.useSpotlight); ImGui::SameLine();
    ImGui::Checkbox("Use Direct3D?", (bool*)&m_lightModel.useDirect3D);
    ImGui::DragFloat("Spot Exponent", &m_lightModel.spotExponent, 0.5f, 0.0f, 500.0f);
    ImGui::DragFloat("Spot Opening", &m_lightModel.spotOpeningAngle, 0.5f, 0.0f, 360.0f);
    
    if (ImGui::Button("Preset color"))
    {
	    m_lights[0] =
        {
            {0.1f, 0.0f, 0.0f, 0.0f},
            {1.0f, 0.2f, 0.2f, 0.0f},
            {0.5f, 0.1f, 0.1f, 0.0f},
            {1.5f, 2.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };    
        m_lights[1] =
        {
            {0.0f, 0.1f, 0.0f, 0.0f},
            {0.2f, 1.0f, 0.2f, 0.0f},
            {0.1f, 0.5f, 0.1f, 0.0f},
            {-1.5f, 1.0f, 1.5f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };
        m_lights[2] =
        {
            {0.0f, 0.0f, 0.1f, 0.0f},
            {0.2f, 0.2f, 1.0f, 0.0f},
            {0.1f, 0.1f, 0.5f, 0.0f},
            {0.0f, 1.0f, -2.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };
    }
    ImGui::SameLine();
    if (ImGui::Button("Preset 1 white"))
    {
	    m_lights[0] =
        {
            {0.1f, 0.1f, 0.1f, 0.0f},
            {1.0f, 1.0f, 1.0f, 0.0f},
            {0.5f, 0.5f, 0.5f, 0.0f},
            {1.5f, 2.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };    
        m_lights[1] =
        {
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {-1.5f, 1.0f, 1.5f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };
        m_lights[2] =
        {
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, -2.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };
    }
    ImGui::SameLine();
    if (ImGui::Button("Preset 3 white"))
    {
	    m_lights[0] =
        {
            {0.1f, 0.1f, 0.1f, 0.0f},
            {1.0f, 1.0f, 1.0f, 0.0f},
            {0.5f, 0.5f, 0.5f, 0.0f},
            {1.5f, 2.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };    
        m_lights[1] =
        {
            {0.1f, 0.1f, 0.1f, 0.0f},
            {1.0f, 1.0f, 1.0f, 0.0f},
            {0.5f, 0.5f, 0.5f, 0.0f},
            {-1.5f, 1.0f, 1.5f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };
        m_lights[2] =
        {
            {0.1f, 0.1f, 0.1f, 0.0f},
            {1.0f, 1.0f, 1.0f, 0.0f},
            {0.5f, 0.5f, 0.5f, 0.0f},
            {0.0f, 1.0f, -2.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 0.0f}
        };
    }
    
    if (ImGui::TreeNode("Light 1"))
    {
        ImGui::ColorEdit3("Ambient##l1", &m_lights[0].ambient[0]);
        ImGui::ColorEdit3("Diffuse##l1", &m_lights[0].diffuse[0]);
        ImGui::ColorEdit3("Specular##l1", &m_lights[0].specular[0]);
        ImGui::DragFloat3("Position##l1", &m_lights[0].position[0], 0.1f, 0.0f, 0.0f);
        ImGui::DragFloat2("Orientation##l1", &orientation[0][0], 0.1f, -360.0f, 360.0f);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Light 2"))
    {
        ImGui::ColorEdit3("Ambient##l2", &m_lights[1].ambient[0]);
        ImGui::ColorEdit3("Diffuse##l2", &m_lights[1].diffuse[0]);
        ImGui::ColorEdit3("Specular##l2", &m_lights[1].specular[0]);
        ImGui::DragFloat3("Position##l2", &m_lights[1].position[0], 0.1f, 0.0f, 0.0f);
        ImGui::DragFloat2("Orientation##l2", &orientation[1][0], 0.1f, -360.0f, 360.0f);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Light 3"))
    {
        ImGui::ColorEdit3("Ambient##l3", &m_lights[2].ambient[0]);
        ImGui::ColorEdit3("Diffuse##l3", &m_lights[2].diffuse[0]);
        ImGui::ColorEdit3("Specular##l3", &m_lights[2].specular[0]);
        ImGui::DragFloat3("Position##l3", &m_lights[2].position[0], 0.1f, 0.0f, 0.0f);
        ImGui::DragFloat2("Orientation##l3", &orientation[2][0], 0.1f, -360.0f, 360.0f);
        ImGui::TreePop();
    }

    ImGui::End();
}

