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
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);


class Renderer {
public:
    Renderer() {}
    void InitScene();
    void InitRenderer();
    void InitCamera();
    void Run();
private:
    std::unique_ptr<GLFWwindow*> window;
    std::vector<unsigned int> VAO;
    std::vector<unsigned int> VBO;
    std::vector<unsigned int> shaders;
    GLuint shaderProgram;
    std::unique_ptr<Scene*> scene;
};



#endif //RENDERER_H
