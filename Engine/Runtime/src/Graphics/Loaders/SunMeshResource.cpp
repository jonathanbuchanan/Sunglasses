#include "SunMeshResource.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

SunMeshResource::SunMeshResource(aiMesh *_mesh) : mesh(_mesh) {

}

void SunMeshResource::init() {
    // Loop through the vertices
    for (size_t i = 0; i < mesh->mNumVertices; ++i) {
        SunVertex vertex;

        // Assign the position
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z;

        // Assign the normal
        vertex.normal.x = mesh->mNormals[i].x;
        vertex.normal.y = mesh->mNormals[i].y;
        vertex.normal.z = mesh->mNormals[i].z;

        // Check for texture coordinates
        if (mesh->mTextureCoords[0]) {
            // Assign the texture coordinates
            vertex.textureCoordinates.x = mesh->mTextureCoords[0][i].x;
            vertex.textureCoordinates.y = mesh->mTextureCoords[0][i].y;

            // Assign the tangent space coordinates
            // FIX ME
            /*vertex.tangent.x = mesh->mTangents[i].x;
            vertex.tangent.y = mesh->mTangents[i].y;
            vertex.tangent.z = mesh->mTangents[i].z;*/
        }

        vertices.push_back(vertex);
    }

    // Loop through the faces
    for (size_t i = 0; i < mesh->mNumFaces; ++i) {
        // Get the face
        aiFace face = mesh->mFaces[i];

        // Loop through the indices
        for (size_t j = 0; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Generate the VAO
    glGenVertexArrays(1, &VAO);

    // Generate the VBO and EBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Initialize and write the data for the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SunVertex), &vertices[0], GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Initialize and write the data for the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

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
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}
