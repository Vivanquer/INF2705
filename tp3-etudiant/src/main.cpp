#include <iostream>
#include <chrono>

#include <GL/glew.h>

#include "imgui/imgui.h"

#include "window.h"
#include "resources.h"

#include "scenes/scene_stencil.h"
#include "scenes/scene_lighting.h"

#include "corrector.h"

void printGLInfo();

int main(int argc, char* argv[])
{
    const bool VSYNC = false;
    Window w;
    if (!w.init(VSYNC))
        return -1;
    
    GLenum rev = glewInit();
    if (rev != GLEW_OK)
    {
        std::cout << "Could not initialize glew! GLEW_Error: " << glewGetErrorString(rev) << std::endl;
        return -2;
    }
        
    printGLInfo();
    
    //corrector(w);
    
    bool isMouseMotionEnabled = false;
    
    Resources res;
    
    SceneStencil  s1(res, isMouseMotionEnabled);
    SceneLighting s2(res, isMouseMotionEnabled);
    
    glClearColor(0.75f, 0.95f, 0.95f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    const char* const SCENE_NAMES[] = {
        "Stencil",
        "Lighting",
    };
    const int N_SCENE_NAMES = sizeof(SCENE_NAMES) / sizeof(SCENE_NAMES[0]);
    int currentScene = 0;
    
    std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now(); 
    
    bool isRunning = true;
    while (isRunning)
    {
        std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastTime;
        double dt = elapsed.count();
        lastTime = currentTime;
        
        if (dt > 1.0)
            dt = 0.0; // skip frame update
    
        if (w.shouldResize())
            glViewport(0, 0, w.getWidth(), w.getHeight());
        
        // TODO: Pour scène de stencil
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ImGui::Begin("Scene Parameters");
        ImGui::Combo("Scene", &currentScene, SCENE_NAMES, N_SCENE_NAMES);
        ImGui::End();
        
        if (w.getKeyPress(Window::Key::SPACE))
            isMouseMotionEnabled = !isMouseMotionEnabled;
            
        if (isMouseMotionEnabled)
            w.hideMouse();
        else
            w.showMouse();
        
        if (w.getKeyPress(Window::Key::T))
            currentScene = ++currentScene < N_SCENE_NAMES ? currentScene : 0;
        
        switch (currentScene)
        {
            case 0: s1.run(w, dt); break;
            case 1: s2.run(w, dt); break;
        }       
        
        w.swap();
        w.pollEvent();
        isRunning = !w.shouldClose() && !w.getKeyPress(Window::Key::ESC);
    }

    return 0;
}


void printGLInfo()
{
    std::cout << "OpenGL info:"          << std::endl;
    std::cout << "    Vendor: "          << glGetString(GL_VENDOR)                   << std::endl;
    std::cout << "    Renderer: "        << glGetString(GL_RENDERER)                 << std::endl;
    std::cout << "    Version: "         << glGetString(GL_VERSION)                  << std::endl;
    std::cout << "    Shading version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}


