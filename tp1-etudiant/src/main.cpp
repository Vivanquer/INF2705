#include <iostream>

#include <GL/glew.h>

#include "imgui/imgui.h"

#include "window.h"
#include "resources.h"

#include "scenes/scene_triangle.h"
#include "scenes/scene_square.h"
#include "scenes/scene_colored_triangle.h"
#include "scenes/scene_colored_square.h"
#include "scenes/scene_draw_elements.h"
#include "scenes/scene_multiple_vbos.h"
#include "scenes/scene_shared_vao.h"
#include "scenes/scene_cube.h"

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
    
    Resources res;
    
    SceneTriangle        s1(res);
    SceneSquare          s2(res);
    SceneColoredTriangle s3(res);
    SceneColoredSquare   s4(res);
    SceneMultipleVbos    s5(res);
    SceneDrawElements    s6(res);
    SceneSharedVao       s7(res);
    SceneCube            s8(res);
    
    
    // TODO - couleur de remplissage suite au nettoyage de l'écran
    //      - test de profondeur
    
    const char* const SCENE_NAMES[] = {
        "First Triangle",
        "First Square",
        "Colored Triangle",
        "Colored Square",
        "Multiple vbos",
        "Draw Elements",
        "Shared vao triangle",
        "Shared vao square",
        "3D Cube"
    };
    const int N_SCENE_NAMES = sizeof(SCENE_NAMES) / sizeof(SCENE_NAMES[0]);
    int currentScene = 0;
    
    bool isRunning = true;
    while (isRunning)
    {
        if (w.shouldResize())
            glViewport(0, 0, w.getWidth(), w.getHeight());
        
        // TODO nettoyage des tampons appropriés
        
        ImGui::Begin("Scene Parameters");
        ImGui::Combo("Scene", &currentScene, SCENE_NAMES, N_SCENE_NAMES);
        ImGui::End();
                
        if (w.getKeyPress(Window::Key::T))
            currentScene = ++currentScene < N_SCENE_NAMES ? currentScene : 0;
        
        switch (currentScene)
        {
            case 0: s1.run(w);        break;
            case 1: s2.run(w);        break;
            case 2: s3.run(w);        break;
            case 3: s4.run(w);        break;
            case 4: s5.run(w);        break;
            case 5: s6.run(w);        break;
            case 6: s7.runTriangle(); break;
            case 7: s7.runSquare();   break;
            case 8: s8.run(w);        break;
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


