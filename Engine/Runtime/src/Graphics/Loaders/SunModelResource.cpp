// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunModelResource.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


SunModelResource::SunModelResource(std::string _path) : path(_path) {

}

void SunModelResource::init() {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

    // Loop through meshes
    for (size_t i = 0; i < scene->mNumMeshes; i++) {
        // Get mesh
        const aiMesh *mesh = scene->mMeshes[i];

        // Get name
        std::string name = std::string(mesh->mName.C_Str());
    }
}

SunMeshData & SunModelResource::getMesh(std::string mesh) {
    return *(meshes[mesh].get());
}

void SunModelResource::addMesh(std::string name, SunMeshData *mesh) {
    // Generate the VAO
    glGenVertexArrays(1, &mesh->VAO);

    // Generate the VBO and EBO
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    // Bind the VAO
    glBindVertexArray(mesh->VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);

    // Initialize and write the data for the VBO
    glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(SunVertex), &mesh->vertices[0], GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);

    // Initialize and write the data for the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(GLuint), &mesh->indices[0], GL_STATIC_DRAW);

    // Initialize and set the vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SunVertex), (GLvoid *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SunVertex), (GLvoid *)offsetof(SunVertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(SunVertex), (GLvoid *)offsetof(SunVertex, tangent));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(SunVertex), (GLvoid *)offsetof(SunVertex, textureCoordinates));

    glEnableVertexAttribArray(4);
    glVertexAttribIPointer(4, 4, GL_INT, sizeof(SunVertex), (GLvoid *)offsetof(SunVertex, boneIDs));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(SunVertex), (GLvoid *)offsetof(SunVertex, boneWeights));

    // Unbind the buffers
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);

    meshes[name] = std::unique_ptr<SunMeshData>(mesh);
}
