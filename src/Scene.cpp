//
// Created by bigbeev on 7/25/2025.
//

#include "Scene.h"

Scene::Scene() {
    filePaths.push_back("D:/dev/cpp/ducky/assets/cube.obj");
    for (auto path: filePaths) {
        objMeshes.push_back(std::make_unique<OBJMesh*>(new OBJMesh(path)));
    }
}