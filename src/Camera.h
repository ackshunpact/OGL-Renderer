//
// Created by bigbeev on 7/25/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <fmt/printf.h>
#include <glm/fwd.hpp>
#include <glm/ext.hpp>
#include <glm/detail/type_quat.hpp>
#include "PerspectiveProjectionInfo.h"

struct PerspectiveProjectionInfo;

class Camera {
public:
    Camera(const glm::vec3& pos, const glm::vec3& target,
        const glm::vec3& up, const PerspectiveProjectionInfo *ppInfo);
    const glm::mat4& getProjMatrix() const { return ppMat; }
    const glm::vec3 getPosition() const;
    const glm::mat4 getView() const;
    const glm::mat4 getVPMat() const;
    void report() {
        fmt::printf("(%f, %f, %f)-(%f, %f, %f)-(%f, %f, %f)-(%f, %f, %f)\n",
            this->pos.x, this->pos.y, this->pos.z,
            this->cameraFront.x, this->cameraFront.y, this->cameraFront.z,
            this->cameraRight.x, this->cameraRight.y, this->cameraRight.z,
            this->cameraUp.x, this->cameraUp.y, this->cameraUp.z);
    }

    void updateCameraVectors();

    float yaw;
    float pitch;

    glm::vec3 direction;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;
    glm::vec3 worldUp;

    glm::mat4 ppMat = glm::mat4(0.0f);
    glm::vec3 pos = glm::vec3(0.0f);
    glm::quat orientation;

};



#endif //CAMERA_H
