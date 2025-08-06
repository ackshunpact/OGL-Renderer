//
// Created by bigbeev on 7/25/2025.
//

#ifndef OBJMESH_H
#define OBJMESH_H
#include <vector>
#include <tiny_obj_loader.h>
#include <filesystem>
#include <fmt/printf.h>
#include "Vertex.h"

class OBJMesh {
public:
    std::vector<Vertex> vertices;
    OBJMesh(const std::string& filePath);

    int loadOBJFromFile(const std::filesystem::path &path, std::vector<Vertex> &vertexData);
};



#endif //OBJMESH_H
