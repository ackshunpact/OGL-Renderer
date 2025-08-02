//
// Created by bigbeev on 7/25/2025.
//

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>
#include <glm/glm.hpp>



namespace Common {


    inline int width = 800;
    inline int height = 600;
    inline float zNear = 0.1f;
    inline float zFar = 100.0f;
    inline float horizontalAngle = 3.14f;
    inline float verticalAngle = 0.0f;
    inline float initialFoV = 45.0f;
    inline float speed =10.0f;
    inline float mouseSpeed = 0.08f;

    // Callback related
    inline float prevMouseX, prevMouseY;
    inline bool firstMouse = true;
    inline float scrollTranslateObjectSpacing = 1.0f;
    inline float currentTranslateObjectSpacing = 1.0f;

    // Render feature flags
    inline bool flagChanged = false;
    inline bool renderWireframe = false;



    inline const std::string pFile = "D:/dev/cpp/ducky/assets/cat_obj/cat.obj";
    // inline const std::string pFile = "D:/dev/cpp/ducky/assets/cube.obj";


    inline bool W_PRESSED = false;
    inline bool A_PRESSED = false;
    inline bool S_PRESSED = false;
    inline bool D_PRESSED = false;
    inline bool SPACE_PRESSED = false;
    inline bool Z_PRESSED = false;

    inline glm::vec3 direction;
    inline glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    inline glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    inline glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);



    inline const char *vertex_shader =
            "#version 330 core\n"
            "layout (location=0) in vec3 aPos;\n"
            "layout (location=1) in vec3 aNorm;\n"
            "layout (location=2) in vec3 aColor;\n"
            "out vec3 normColor;"
            "uniform mat4 transform;\n"
            "void main() {\n"
            "  gl_Position = transform * vec4( aPos, 1.0 );\n"
            "  normColor = aNorm;\n"
            "}\0";

    inline const char *fragment_shader =
            "#version 330 core\n"
            "in vec3 normColor;\n"
            "out vec4 frag_colour;\n"
            "uniform vec3 ourColor;\n"
            "void main() {\n"
            "  frag_colour = vec4(normColor, 1.0);\n"
            "}\0";
};

#endif //DEFINITIONS_H
