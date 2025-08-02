//
// Created by bigbeev on 8/1/2025.
//

#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <vector>
#include <GL/gl.h>
#include <glm/vec2.hpp>


struct Image {
    GLuint width, height;
    std::vector<uint8_t> data;

    Image subImage(glm::uvec2 offset, glm::uvec2 extent) const;
};


#endif //IMAGE_H
