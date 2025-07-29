//
// Created by bigbeev on 7/25/2025.
//

#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
// #include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

Camera::Camera(const glm::vec3& pos, const glm::vec3& target,
               const glm::vec3& up, const PerspectiveProjectionInfo *ppInfo) {
    this->pos = pos;
    this->direction = glm::normalize(target - pos);
    this->cameraFront = this->direction;
    this->cameraRight = glm::normalize(glm::cross(this->cameraFront, this->worldUp));
    this->cameraUp = glm::normalize(glm::cross(this->cameraRight, this->cameraFront));

    this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    float aspectRatio = float(ppInfo->width) / float(ppInfo->height);
    // this->orientation = glm::quat_cast(glm::lookAtLH(pos, cameraFront, cameraUp));
    glm::mat3 rotMatrix(cameraRight, cameraUp, -cameraFront);
    orientation = glm::quat_cast(rotMatrix);
    this->ppMat = glm::perspectiveLH(ppInfo->fov, aspectRatio, 0.01f, 100.0f);
    yaw = glm::degrees(atan2(direction.z, direction.x));

    pitch = glm::degrees(asin(direction.y));

}

const glm::vec3 Camera::getPosition() const {
    return this->pos;
}
const glm::mat4 Camera::getView() const {
    return glm::lookAtLH(pos, pos + cameraFront, cameraUp);

}
const glm::mat4 Camera::getVPMat() const {
    glm::mat4 v = getView();
    glm::mat4 p = getProjMatrix();
    return p * v;
}

void Camera::updateCameraVectors() {
    // Calculate new front vector
    // glm::vec3 newFront;
    // newFront.x = cos(yaw) * cos(pitch);
    // newFront.y = sin(pitch);
    // newFront.z = sin(yaw) * cos(pitch);
    // printf("<%f, %f>\n", yaw, pitch);
    // cameraFront = glm::normalize(newFront);
    // direction = cameraFront; // Keep direction in sync
    //
    // // Recalculate right and up vectors
    // cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    // cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
    //
    // // Update orientation quaternion to match new vectors
    // glm::mat3 rotMatrix(cameraRight, cameraUp, -cameraFront);
    // orientation = glm::quat_cast(rotMatrix);
}