// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/SunMesh.h>

#include <sunglasses/Core/SunObject.h>

#include <sunglasses/Graphics/Loaders/SunMeshResource.h>
#include <sunglasses/Graphics/Loaders/SunMaterialResource.h>

#include <glm/gtc/type_ptr.hpp>

SunMesh::SunMesh() {

}

SunMesh::SunMesh(SunObject *_object, SunMeshResource *_mesh, SunMaterialResource *_material) : object(_object), mesh(_mesh), material(_material), scale(glm::vec3(1.0f, 1.0f, 1.0f)) {

}

SunMesh::SunMesh(SunObject *_object, SunMeshResource *_mesh, SunMaterialResource *_material, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) : object(_object), mesh(_mesh), material(_material), position(_position), rotation(_rotation), scale(_scale) {

}

void SunMesh::render(SunShader *shader) {
    material->pass(shader, "material");

    glm::vec3 _position = object->getPosition() + position;
    glm::vec3 _rotation = object->getRotation() + rotation;
    glm::vec3 _scale = object->getScale() * scale;

    // Calculate the model matrix
    glm::mat4 modelMatrix = glm::mat4();
    modelMatrix = glm::translate(modelMatrix, _position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0, 0.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0, 1.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0, 0.0, 1.0));
    modelMatrix = glm::scale(modelMatrix, _scale);

    // Pass the model matrix uniform
    (*shader)["model"] = modelMatrix;

    // Calculate the normal matrix
    glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

    // Pass the normal matrix
    (*shader)["normalMatrix"] = normalMatrix;

    // Bind the VAO
    glBindVertexArray(mesh->getVAO());

    // Draw the triangles
    glDrawElements(GL_TRIANGLES, mesh->getIndicesSize(), GL_UNSIGNED_INT, 0);

    // Unbind the VAO
    glBindVertexArray(0);
}
