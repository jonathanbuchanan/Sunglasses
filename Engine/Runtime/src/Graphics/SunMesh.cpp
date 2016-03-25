// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunMesh.h"

#include "Loaders/SunMeshResource.h"
#include "../Extern/SunResourceService.h"

SunMesh::SunMesh(std::vector<SunVertex> _vertices, std::vector<GLuint> _indices, std::vector<SunTexture> _textures, std::vector<SunBone> _bones, std::vector<SunAnimation> _animations) {
    //vertices = _vertices;
    indices = _indices;
    //textures = _textures;
    //bones = _bones;
    //animations = _animations;

    //calculateBindPoseAndInverseBindPose();

    // Set up the OpenGL stuff
    //setUpGL();
}

void SunMesh::init() {

}

void SunMesh::setUpGL() {
    // Generate the VAO
    /*glGenVertexArrays(1, &VAO);

    // Generate the VBO and EBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind the VAO
    glBindVertexArray(VAO);

    // Bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Initialize and write the data for the VBO
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof (SunVertex), &vertices[0], GL_STATIC_DRAW);

    // Bind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Initialize and write the data for the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof (GLuint), &indices[0], GL_STATIC_DRAW);

    // Initialize and set the vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof (SunVertex), (GLvoid *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof (SunVertex), (GLvoid *) offsetof(SunVertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof (SunVertex), (GLvoid *) offsetof(SunVertex, tangent));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof (SunVertex), (GLvoid *) offsetof(SunVertex, textureCoordinates));

    glEnableVertexAttribArray(4);
    glVertexAttribIPointer(4, 4, GL_INT, sizeof (SunVertex), (GLvoid *) offsetof(SunVertex, boneIDs));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof (SunVertex), (GLvoid *) offsetof(SunVertex, boneWeights));

    // Unbind the VBO and EBO
    glBindVertexArray(0);*/
}

void SunMesh::calculateBindPoseAndInverseBindPose() {
    for (size_t i = 0; i < bones.size(); i++) {
        if (bones[i].parentID == -1) {
            bones[i].globalTransform = bones[i].relativeTransform;
        } else {
            bones[i].globalTransform = bones[bones[i].parentID].globalTransform * bones[i].relativeTransform;
        }
    }
}

void SunMesh::calculateBoneGlobalTransforms(GLfloat _currentTick) {
    for (size_t i = 0; i < bones.size(); i++) {
        SunAnimationChannel channel = animations[0].channels[i];

        int firstKeyIndex;
        int secondKeyIndex;

        bool onKeyframe = false;

        for (size_t j = 0; j < channel.rotationKeyTicks.size(); j++) {
            if (floor(_currentTick) < round(channel.rotationKeyTicks[j])) {
                firstKeyIndex = j - 1;
                secondKeyIndex = j;
                onKeyframe = false;
                break;
            } else if (floor(_currentTick) == round(channel.rotationKeyTicks[j])) {
                firstKeyIndex = j;
                secondKeyIndex = j;
                onKeyframe = true;
                break;
            }
        }

        if (onKeyframe == false) {
            GLfloat deltaTime = channel.rotationKeyTicks[secondKeyIndex] - channel.rotationKeyTicks[firstKeyIndex];
            GLfloat factor = (_currentTick - channel.rotationKeyTicks[firstKeyIndex]) / deltaTime;

            glm::quat startQuaternion = channel.rotationKeyValues[firstKeyIndex];
            glm::quat endQuaternion = channel.rotationKeyValues[secondKeyIndex];

            glm::quat interpolatedQuaternion = glm::slerp(startQuaternion, endQuaternion, factor);

            bones[i].relativeTransform = glm::toMat4(interpolatedQuaternion);
        } else {
            bones[i].relativeTransform = glm::toMat4(channel.rotationKeyValues[firstKeyIndex]);
        }

        if (bones[i].parentID == -1) {
            bones[i].globalTransform = bones[i].relativeTransform;
        } else {
            bones[i].globalTransform = bones[bones[i].parentID].globalTransform * bones[i].relativeTransform;
        }
    }
}

void SunMesh::passGlobalTransformUniforms(SunShader _shader) {
    for (size_t i = 0; i < bones.size(); i++) {
        glm::mat4 boneMatrix = bones[i].globalTransform * globalInverseTransform;

        glUniformMatrix4fv(_shader.getUniformLocation(("boneMatrices[" + std::to_string(i) + "]")), 1, GL_FALSE, glm::value_ptr(boneMatrix));
    }
}

void SunMesh::render(SunShader _shader, GLfloat _deltaTime, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, SunObjectMaterial _material, SunMeshRenderType _renderType) {
    if (_renderType == SunMeshRenderTypeTextured && textures.size() > 0) {
        glBindTexture(GL_TEXTURE_2D, textures[0].id);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(_shader.getUniformLocation("material.diffuse"), 0);

        glUniform1f(_shader.getUniformLocation("material.shininess"), _material.shininess);

        // Calculate the model matrix
        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(modelMatrix, _position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0, 0.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0, 1.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0, 0.0, 1.0));
        modelMatrix = glm::scale(modelMatrix, _scale);

        // Pass the model matrix uniform
        glUniformMatrix4fv(_shader.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

        // Calculate the normal matrix
        glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));

        // Pass the normal matrix
        glUniformMatrix3fv(_shader.getUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

        // Bind the VAO
        SunResource *mesh = ((SunResourceService *)getService("resource_service"))->getResourceManager("meshes")->getResource("Teapot");
        glBindVertexArray(((SunMeshResource *)mesh)->getVAO());

        // Draw the triangles
        glDrawElements(GL_TRIANGLES, ((SunMeshResource *)mesh)->getIndicesSize(), GL_UNSIGNED_INT, 0);

        // Unbind the VAO
        glBindVertexArray(0);
    } else {
        glUniform3f(_shader.getUniformLocation("material.diffuse"), _material.color.r, _material.color.g, _material.color.b);

        glUniform1f(_shader.getUniformLocation("material.shininess"), _material.shininess);

        // Calculate the model matrix
        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(modelMatrix, _position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0, 0.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0, 1.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0, 0.0, 1.0));
        modelMatrix = glm::scale(modelMatrix, _scale);

        // Pass the model matrix uniform
        glUniformMatrix4fv(_shader.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

        // Calculate the normal matrix
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

        // Pass the normal matrix
        glUniformMatrix3fv(_shader.getUniformLocation("normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));

        // Bind the VAO
        //glBindVertexArray(VAO);
        SunResource *mesh = ((SunResourceService *)getService("resource_service"))->getResourceManager("meshes")->getResource("Teapot");



        glBindVertexArray(((SunMeshResource *)mesh)->getVAO());

        // Draw the triangles
        glDrawElements(GL_TRIANGLES, ((SunMeshResource *)mesh)->getIndicesSize(), GL_UNSIGNED_INT, 0);

        // Unbind the VAO
        glBindVertexArray(0);
    }
}
