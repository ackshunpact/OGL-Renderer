//
// Created by bigbeev on 7/25/2025.
//

#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>


Camera::Camera(const glm::vec3& pos, const glm::vec3& target,
               const glm::vec3& up, const PerspectiveProjectionInfo *ppInfo) {
    this->pos = pos;
    float aspectRatio = float(ppInfo->width) / float(ppInfo->height);
    this->orientation = glm::lookAtLH(pos, target, up);
    this->ppMat = glm::perspectiveLH(ppInfo->fov, aspectRatio, 0.01f, 100.0f);
}

const glm::vec3 Camera::getPosition() const {
    return glm::vec3(pos.x, pos.y, pos.z);
}
const glm::mat4 Camera::getView() const {
    glm::mat4 t = glm::translate(glm::mat4(1.0f), -pos);
    glm::mat4 r = glm::mat4_cast(this->orientation);
    glm::mat4 res = r * t;
    return res;
}
const glm::mat4 Camera::getVPMat() const {
    glm::mat4 v = getView();
    glm::mat4 p = getProjMatrix();
    return p * v;
}