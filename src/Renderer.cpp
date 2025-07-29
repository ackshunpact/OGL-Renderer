//
// Created by bigbeev on 7/25/2025.
//

#include "Renderer.h"
#include <iostream>
#include <bits/ostream.tcc>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>



void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

const char *vertex_shader =
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

const char *fragment_shader =
        "#version 330 core\n"
        "in vec3 normColor;\n"
        "out vec4 frag_colour;\n"
        "uniform vec3 ourColor;\n"
        "void main() {\n"
        "  frag_colour = vec4(abs(normColor.x), abs(normColor.y), abs(normColor.z), 1.0);\n"
        "}\0";

Renderer::Renderer() {
    InitScene();
    InitRenderer();
}

void Renderer::InitRenderer() {
    window = std::make_unique<Window>();
    int loaded = gladLoadGL();
    if (!loaded) {
        printf("Failed to load GL\n");
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);


    unsigned int VAO, VBO1;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    VAOs.push_back(VAO);

    std::vector<OBJMesh*> verts = scene->objMeshes;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, verts[0]->vertices.size() * sizeof(Vertex), verts[0]->vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));



    int success;
    char infoLog[512];

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fs, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


}


void Renderer::Run() {
    float prevTime = float(window->markTime());
    while (!window->checkWindowshouldClose()) {
        float currTime = float(window->markTime());
        float deltaTime = currTime - prevTime;
        window->pollEvents();

        auto verts = scene.get()->objMeshes[0]->vertices;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5.0f));
        glm::mat4 ProjMatrix = glm::perspectiveFov(45.0f, 800.f, 600.f, 0.01f, 100.0f);

        // glm::mat4 MVP = ProjMatrix * ViewMatrix * ModelMatrix;
        glm::mat4 MVP = window->GetVPMatrix();

        glm::vec3 color(1.0, 0.0, 1.0);
        GLint colorLoc = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform3fv(colorLoc, 1, glm::value_ptr(color));


        GLint transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &MVP[0][0]);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, verts.size());
        // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        window->updateCamera(deltaTime);
        window->swapBuffers();
        prevTime = currTime;
    }

}


void Renderer::InitScene() {
    this->scene = std::make_unique<Scene>(Scene());
}