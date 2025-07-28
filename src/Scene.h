//
// Created by bigbeev on 7/25/2025.
//

#ifndef SCENE_H
#define SCENE_H
#include <vector>

#include "OBJMesh.h"


class Scene {
public:
    std::vector<OBJMesh*> objMeshes;
    std::vector<std::string> filePaths;
    Scene();
    std::vector<OBJMesh*> getObjMeshes() { return objMeshes; }

};




#endif //SCENE_H
