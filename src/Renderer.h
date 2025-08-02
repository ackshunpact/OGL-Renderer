//
// Created by bigbeev on 7/25/2025.
//

#ifndef RENDERER_H
#define RENDERER_H
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "Scene.h"
#include <memory>
#include <vector>
#include "Definitions.h"
#include "ImageRegistry.h"
#include "Shader.h"
#include "Window.h"


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);


class Renderer {
public:
    Renderer();
    void InitScene();
    void InitTextures();
    void InitRenderer();
    void Run();

    void ProcessFlags();


private:
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> shaders;
    std::vector<unsigned int> textures;

    Shader* defaultShader;
    ImageRegistry *iReg;
    unsigned int tex1;
    std::unique_ptr<Window> window ;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Camera> camera;
};



#endif //RENDERER_H
