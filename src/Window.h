//
// Created by bigbeev on 7/28/2025.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <glfw/glfw3.h>
#include <fmt/printf.h>

#include "Camera.h"
#include "Definitions.h"

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);



struct DestroyglfwWin{

    void operator()(GLFWwindow* ptr){
        glfwDestroyWindow(ptr);
    }

};

class Window {
public:
    Window();
    void Init();
    void InitCamera();
    double markTime();
    Camera* GetCamera();
    void updateCamera(float deltaTime);
    void UpdatePosition(float deltaTime);
    void UpdateCameraPosition(float deltaTime);
    void UpdateCameraVectors();
    glm::mat4 GetVPMatrix();

    void processMouseMovement(float xOffset, float yOffset);
    bool checkWindowshouldClose();
    void pollEvents();
    void swapBuffers();


    std::unique_ptr<GLFWwindow, DestroyglfwWin> window;
    std::unique_ptr<Camera> camera;
};



#endif //WINDOW_H
