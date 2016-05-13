// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "Chunk.h"

#include "Block.h"

void Chunk::init() {
    addAction("render", &Chunk::render);
    addAction("update", &Chunk::update);

    addTag("textured");

    for (int x = 0; x < 16; ++x)
        for (int y = 0; y < 8; ++y)
            for (int z = 0; z < 16; ++z) {
                if ((x + y + z) % 2 == 0) {
                    blocks[x][y][z] = new Block();
                    blocks[x][y][z]->init();
                }
                //blocks[x][y][z].setPosition(glm::vec3(x, y, z));
            }

    generateMesh();
}

void Chunk::update(SunAction action) {

}

void Chunk::render(SunAction action) {
    SunShader *shader = action.getParameterPointer<SunShader>("shader");

    SunMaterialResource *material = ((SunMaterialResource *)services->get<SunResourceService>()->getResourceManager("materials")->getResource("grass"));
    material->pass(shader, "material");

    /*glm::vec3 _position = position;
    glm::vec3 _rotation = rotation;
    glm::vec3 _scale = scale;*/

    // Calculate the model matrix
    glm::mat4 modelMatrix = glm::mat4();
    /*modelMatrix = glm::translate(modelMatrix, _position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0, 0.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0, 1.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0, 0.0, 1.0));
    modelMatrix = glm::scale(modelMatrix, _scale);*/

    // Pass the model matrix uniform
    glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Calculate the normal matrix
    glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

    // Pass the normal matrix
    glUniformMatrix3fv(shader->getUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

    // Bind the VAO
    glBindVertexArray(VAO);

    // Draw the triangles
    //glDrawElements(GL_TRIANGLES, mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // Unbind the VAO
    glBindVertexArray(0);
}

void Chunk::generateMesh() {
    std::vector<SunVertex> cubeVertices = ((SunMeshResource *)services->get<SunResourceService>()->getResourceManager("meshes")->getResource("Cube"))->getVertices();
    std::vector<GLuint> cubeIndices = ((SunMeshResource *)services->get<SunResourceService>()->getResourceManager("meshes")->getResource("Cube"))->getIndices();

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    for (int x = 0; x < 16; ++x)
        for (int y = 0; y < 128; ++y)
            for (int z = 0; z < 16; ++z) {
                if (blocks[x][y][z] != nullptr) {
                    for (int i = 0; i < cubeIndices.size(); ++i) {
                        indices.push_back(cubeIndices[i] + vertices.size());
                    }
                    for (int i = 0; i < cubeVertices.size(); ++i) {
                        SunVertex vertex = cubeVertices[i];
                        vertex.position += glm::vec3(x * 2, y * 2, z * 2);
                        vertices.push_back(vertex);
                    }
                    vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
                }
            }

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(SunVertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

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

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
