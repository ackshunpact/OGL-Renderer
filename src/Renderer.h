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
#include "Camera.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);


class Renderer {
public:
    Renderer();
    void InitScene();
    void InitRenderer();
    void InitCamera();
    void Run();
private:
    std::unique_ptr<GLFWwindow*> window;
    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> shaders;
    GLuint shaderProgram;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<Camera> camera;
};



#endif //RENDERER_H
