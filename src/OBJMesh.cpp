//
// Created by bigbeev on 7/25/2025.
//

#include "OBJMesh.h"
#include <iostream>


OBJMesh::OBJMesh(const std::string& filePath) {
    loadOBJFromFile(filePath, vertices);
}

int OBJMesh::loadOBJFromFile(const std::filesystem::path &path, std::vector<Vertex> &vertexData) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.string().c_str());

    if (!warn.empty()) {
        printf("%s", warn.c_str());
    }

    if (!err.empty()) {
        printf("%s", err.c_str());
    }

    if (!ret) {
        return false;
    }

    const auto &shape = shapes[0];

    vertexData.resize(shape.mesh.indices.size());
    for (size_t i = 0; i < shape.mesh.indices.size(); ++i) {
        const tinyobj::index_t &idx = shape.mesh.indices[i];

        vertexData[i].position = {
            attrib.vertices[3 * idx.vertex_index + 0],
            attrib.vertices[3 * idx.vertex_index + 1],
            attrib.vertices[3 * idx.vertex_index + 2]
        };

        vertexData[i].normal = {
            attrib.normals[3 * idx.normal_index + 0],
            attrib.normals[3 * idx.normal_index + 1],
            attrib.normals[3 * idx.normal_index + 2]
        };

        vertexData[i].color = {
            attrib.colors[3 * idx.vertex_index + 0],
            attrib.colors[3 * idx.vertex_index + 1],
            attrib.colors[3 * idx.vertex_index + 2]
        };

        vertexData[i].uv = {
        attrib.texcoords[2 * idx.texcoord_index + 0],
        attrib.texcoords[2 * idx.texcoord_index + 1]
        };
    }
    return vertices.size() - 1;
}
