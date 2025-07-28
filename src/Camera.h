//
// Created by bigbeev on 7/25/2025.
//

#ifndef CAMERA_H
#define CAMERA_H

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

private:
    glm::mat4 ppMat = glm::mat4(0.0f);
    glm::vec3 pos = glm::vec3(0.0f);
    glm::quat orientation = glm::quat(glm::vec3(0.0f));
};



#endif //CAMERA_H
