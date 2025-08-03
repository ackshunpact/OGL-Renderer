//
// Created by bigbeev on 7/25/2025.
//

#include "Renderer.h"
#include <iostream>
#include <bits/ostream.tcc>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include "ShaderManager.h"


void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
std::vector<glm::vec3> generatePositionMatrices();



Renderer::Renderer() {
    iReg = new ImageRegistry();
    iReg->insert("wall1", "D:/dev/cpp/ducky/assets/wall.jpg");
    shaderManager = ShaderManager::getInstance();
    InitScene();
    // InitTextures();
    InitRenderer();
    InitShaders();
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

    std::shared_ptr<Image> img = iReg->get("wall1");

    glGenTextures(1, &tex1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, img->width, img->height, 0, GL_BGR, GL_UNSIGNED_BYTE, img->data.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));



}


void Renderer::Run() {
    std::vector<glm::vec3> offset_Instances = generatePositionMatrices();
    GLuint instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, offset_Instances.size() * sizeof(glm::vec3), offset_Instances.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1);

    float translationFactor = 1.0f;
    float translationAccumulator = 0.0f;
    float prevTime = float(window->markTime());
    while (!window->checkWindowshouldClose()) {
        if (Common::flagChanged) {
            printf("process flags() invoked\n");
            ProcessFlags();
        }
        float currTime = float(window->markTime());
        float deltaTime = currTime - prevTime;
        window->pollEvents();

        auto verts = scene.get()->objMeshes[0]->vertices;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderManager->useShader("default");
        glm::mat4 MVP = window->GetVPMatrix();

        glm::vec3 color(1.0, 0.0, 1.0);
        // GLint colorLoc = glGetUniformLocation(defaultShader->ID, "ourColor");
        // glUniform3fv(colorLoc, 1, glm::value_ptr(color));
        shaderManager->setUniform("ourColor", color);

        // GLint transformLoc = glGetUniformLocation(defaultShader->ID, "transform");
        // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &MVP[0][0]);
        shaderManager->setUniform("transform", MVP);
        // section
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex1);
        if (translationAccumulator > 10.0f) translationAccumulator =-1.0f;
        else if (translationAccumulator <= 0.0f) translationAccumulator = 1.0f;
        translationAccumulator += deltaTime;
        // defaultShader->setFloat("scrollOffset", 5*sin(translationAccumulator));
        shaderManager->setUniform("scrollOffset", static_cast<float>(5 * sin(translationAccumulator)));
        // // section
        glBindVertexArray(VAOs[0]);
        // glDrawArrays(GL_TRIANGLES, 0, verts.size());
        glDrawArraysInstanced(GL_TRIANGLES, 0, verts.size(), offset_Instances.size());
        window->updateCamera(deltaTime);
        window->swapBuffers();
        prevTime = currTime;
    }

}


void Renderer::InitScene() {
    this->scene = std::make_unique<Scene>(Scene());
}

void Renderer::InitTextures() {
    // Texture(GLuint target, GLint internalFormat, GLint type, bool genMipMap, GLint maxLod) : id(0), target(target),
        // internalFormat(internalFormat), format(0), type(type), genMipMap(genMipMap) {
    std::shared_ptr<Image> img = iReg->get("wall1");
    glGenTextures(1, &tex1);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, img->width, img->height, 0, GL_BGR, GL_UNSIGNED_BYTE, img->data.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 4);




}

void Renderer::InitShaders() {
    shaderManager->loadModule("vertex", "D:/dev/cpp/ducky/shaders/default.vert");
    shaderManager->loadModule("fragment", "D:/dev/cpp/ducky/shaders/default.frag");
    shaderManager->createShader("default", {"vertex"}, {"fragment"});

}


std::vector<glm::vec3> generatePositionMatrices() {
    int NUM_INSTANCES = 1000;
    std::vector<glm::vec3> offsets(NUM_INSTANCES);
    for (int i = -10; i < 10; i+=2) {
        for (int j = -10; j < 10; j+=2) {
            for (int k = -10; k < 10; k+=2) {
                glm::vec3 offset = glm::vec3(static_cast<float>(i), static_cast<float>(j), static_cast<float>(k));
                offsets.push_back(offset);
            }
        }
    }

    return offsets;
}

void Renderer::ProcessFlags() {
    if (Common::renderWireframe) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    } else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    Common::flagChanged = false;
}
