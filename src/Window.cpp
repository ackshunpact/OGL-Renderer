//
// Created by bigbeev on 7/28/2025.
//


#include "Window.h"
Window::Window() {

    Init();
    glfwSetWindowUserPointer(window.get(), this);
}

void Window::Init() {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }
    GLFWwindow* temp = glfwCreateWindow(Common::width, Common::height, "Ducky v0.1", NULL, NULL);
    window = std::unique_ptr<GLFWwindow, DestroyglfwWin>(temp);


    if (!window) {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    glfwSetKeyCallback(window.get(), key_callback);
    glfwSetCursorPosCallback(window.get(), cursor_position_callback);
    glfwSetScrollCallback(window.get(), scroll_callback);


    // glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwMakeContextCurrent(window.get());
    InitCamera();

}

void Window::InitCamera() {
    PerspectiveProjectionInfo perspectiveInfo(Common::width, Common::height, Common::initialFoV, Common::zNear, Common::zFar);
    this->camera = std::make_unique<Camera>(Camera(Common::cameraPos, Common::cameraFront, Common::cameraUp, &perspectiveInfo));
}

double Window::markTime() {
    return glfwGetTime();
}

Camera * Window::GetCamera() {
    return camera.get();
}

void Window::updateCamera(float deltaTime) {
    UpdateCameraPosition(deltaTime);
    UpdateCameraVectors();
    // camera->report();
}



bool Window::checkWindowshouldClose() {
    return glfwWindowShouldClose(window.get());
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::swapBuffers() {
    glfwSwapBuffers(window.get());
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        printf("%d", key);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        Common::S_PRESSED = true;
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        Common::W_PRESSED = true;
    if (key == GLFW_KEY_D && action == GLFW_PRESS)
        Common::D_PRESSED = true;
    if (key == GLFW_KEY_A && action == GLFW_PRESS)
        Common::A_PRESSED = true;

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
        Common::SPACE_PRESSED = true;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        Common::Z_PRESSED = true;
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        Common::renderWireframe = !Common::renderWireframe;
        Common::flagChanged = true;
        printf("toggle renderWireframe %d, flagChanged %d\n", Common::renderWireframe, Common::flagChanged);
    }

    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
        Common::S_PRESSED = false;
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
        Common::W_PRESSED = false;
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
        Common::D_PRESSED = false;
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
        Common::A_PRESSED = false;

    if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
        Common::SPACE_PRESSED = false;
    if (key == GLFW_KEY_Z && action == GLFW_RELEASE)
        Common::Z_PRESSED = false;
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

    if (Common::firstMouse) {
        Common::prevMouseX = Common::width / 2.0f;
        Common::prevMouseY = Common::height / 2.0f;
        Common::firstMouse = false;
    }

    float xOffset = xpos - Common::prevMouseX;
    float yOffset = Common::prevMouseY - ypos;

    Common::prevMouseX = xpos;
    Common::prevMouseY = ypos;
    Window* thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    thisWindow->processMouseMovement(xOffset, yOffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    printf("(%f, %f)\n", xoffset, yoffset);
    Common::scrollTranslateObjectSpacing += yoffset / 10.0f;
}

void Window::processMouseMovement(float xOffset, float yOffset) {
    xOffset *= Common::mouseSpeed;
    yOffset *= Common::mouseSpeed;

    camera->yaw -= glm::radians(xOffset);
    camera->pitch += glm::radians(yOffset);

    UpdateCameraVectors();
}


void Window::UpdateCameraPosition(float deltaTime) {

    if (Common::W_PRESSED == true) {
        camera->pos += camera->cameraFront * Common::speed * deltaTime;
    }
    if (Common::S_PRESSED == true) {
        camera->pos -= camera->cameraFront * Common::speed * deltaTime;
    }
    if (Common::A_PRESSED == true) {
        camera->pos += camera->cameraRight * Common::speed * deltaTime;
    }
    if (Common::D_PRESSED == true) {
        camera->pos -= camera->cameraRight * Common::speed * deltaTime;
    }
    if (Common::SPACE_PRESSED == true) {
        camera->pos += camera->cameraUp * Common::speed * deltaTime;
    }
    if (Common::Z_PRESSED == true) {
        camera->pos -= camera->cameraUp * Common::speed * deltaTime;
    }

}

void Window::UpdateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(camera->yaw) * cos(camera->pitch);
    newFront.y = sin(camera->pitch);
    newFront.z = sin(camera->yaw) * cos(camera->pitch);
    this->camera->cameraFront = glm::normalize(newFront);

    this->camera->cameraRight = glm::normalize(glm::cross(this->camera->cameraFront, this->camera->worldUp));
    this->camera->cameraUp = glm::cross(this->camera->cameraRight, this->camera->cameraFront);
    glm::mat3 rotMatrix(camera->cameraRight, camera->cameraUp, -camera->cameraFront);
    camera->orientation = glm::quat_cast(rotMatrix);
}

glm::mat4 Window::GetVPMatrix() {
    return camera->getVPMat();
}