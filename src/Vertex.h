//
// Created by bigbeev on 7/28/2025.
//

#ifndef VERTEX_H
#define VERTEX_H
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 uv;
};
#endif //VERTEX_H
