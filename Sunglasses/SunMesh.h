//
//  SunMesh.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/13/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunMesh_h
#define OpenGL_Test_3_SunMesh_h

#include <vector>
using namespace std;

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

// SunVertex Declaration
struct SunVertex {
    // Position, normal, and texture coordinates
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 tangent;
    glm::vec2 textureCoordinates;
    GLuint boneIDs[4];
    GLfloat boneWeights[4];
    
    SunVertex() {
        
    }
};

// SunBone Declaration
struct SunBone {
    string name;
    GLint parentID;
    
    glm::mat4 relativeTransform;
    glm::mat4 globalTransform;
    glm::mat4 bindPose;
    glm::mat4 inverseBindPose;
};

// SunAnimationChannel Declaration
struct SunAnimationChannel {
    GLuint boneID;
    
    vector<GLdouble> rotationKeyTicks;
    vector<glm::quat> rotationKeyValues;
};

// SunAnimation Declaration
struct SunAnimation {
    GLdouble length;
    GLdouble ticksPerSecond;
    
    vector<SunAnimationChannel> channels;
};

// SunTexture Declaration
struct SunTexture {
    // Id, type, and path
    GLuint id;
    string type;
    aiString path;
};

// SunObjectMaterial Declaration
struct SunObjectMaterial {
    glm::vec3 color;
    GLfloat shininess;
    
    GLboolean textured;
    GLboolean animated;
};

class SunMesh {
public:
    // Vertices, indices, and textures
    vector<SunVertex> vertices;
    vector<GLuint> indices;
    vector<SunTexture> textures;
    vector<SunBone> bones;
    vector<SunAnimation> animations;
    glm::mat4 globalInverseTransform;
    
    // VBO, EBO, and VAO
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;
    
    SunMesh() {
        
    }
    
    SunMesh(vector<SunVertex> _vertices, vector<GLuint> _indices, vector<SunTexture> _textures, vector<SunBone> _bones, vector<SunAnimation> _animations) {
        // Set vertices, indices, and textures from the parameters
        vertices = _vertices;
        indices = _indices;
        textures = _textures;
        bones = _bones;
        animations = _animations;
        
        calculateBindPoseAndInverseBindPose();
        
        // Set up the OpenGL stuff
        setUpGL();
    }
    
    virtual void setUpGL() {
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SunVertex), (GLvoid *)0);
        
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
        
        // Unbind the VBO and EBO
        glBindVertexArray(0);
    }
    
    void calculateBindPoseAndInverseBindPose() {
        for (int i = 0; i < bones.size(); i++) {
            if (bones[i].parentID == -1) {
                bones[i].globalTransform = bones[i].relativeTransform;
            } else {
                bones[i].globalTransform = bones[bones[i].parentID].globalTransform * bones[i].relativeTransform;
            }
            
            //bones[i].bindPose = bones[i].globalTransform;
            //bones[i].inverseBindPose = glm::inverse(bones[i].bindPose);
        }
    }
    
    void calculateBoneGlobalTransforms(GLfloat _currentTick) {
        for (int i = 0; i < bones.size(); i++) {
            SunAnimationChannel channel = animations[0].channels[i];
            
            int firstKeyIndex;
            int secondKeyIndex;
            
            bool onKeyframe = false;
            
            for (int j = 0; j < channel.rotationKeyTicks.size(); j++) {
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
    
    void passGlobalTransformUniforms(SunShader _shader) {
        for (int i = 0; i < bones.size(); i++) {
            glm::mat4 boneMatrix = bones[i].globalTransform * globalInverseTransform;
            
            glUniformMatrix4fv(glGetUniformLocation(_shader.program, ("boneMatrices[" + to_string(i) + "]").c_str()), 1, GL_FALSE, glm::value_ptr(boneMatrix));
        }
    }
    
    virtual void render(SunShader _shader, GLfloat _deltaTime, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale, SunObjectMaterial _material) {
        /*for (GLuint i = 0; i < textures.size(); i++) {
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
            
            if (i == 0)
                glActiveTexture(GL_TEXTURE0);
            if (i == 1)
                glActiveTexture(GL_TEXTURE1);
            
            glUniform1f(glGetUniformLocation(_shader.program, ("material." + textures[i].type).c_str()), i);
        }*/
        
        if (_material.animated == true) {
            GLfloat tick = glfwGetTime() * animations[0].ticksPerSecond;
            
            calculateBoneGlobalTransforms(fmod(tick, animations[0].length * animations[0].ticksPerSecond));
            passGlobalTransformUniforms(_shader);
        }
        
        if (_material.textured == true) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[0].id);
            glUniform1i(glGetUniformLocation(_shader.program, "material.diffuse"), 0);
            
            /*glActiveTexture(GL_TEXTURE1);
             glBindTexture(GL_TEXTURE_2D, textures[1].id);
             glUniform1i(glGetUniformLocation(_shader.program, "material.normal"), 1);*/
        } else {
            glUniform3f(glGetUniformLocation(_shader.program, "material.color"), _material.color.r, _material.color.g, _material.color.b);
        }
        
        glUniform1f(glGetUniformLocation(_shader.program, "material.shininess"), _material.shininess);
        
        // Calculate the model matrix
        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(modelMatrix, _position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0, 0.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0, 1.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0, 0.0, 1.0));
        modelMatrix = glm::scale(modelMatrix, _scale);
        
        // Pass the model matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(_shader.program, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        
        // Calculate the normal matrix
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
        
        // Pass the normal matrix
        glUniformMatrix3fv(glGetUniformLocation(_shader.program, "normalMatrix"), 1, GL_FALSE, glm::value_ptr(normalMatrix));
        
        // Bind the VAO
        glBindVertexArray(VAO);
        
        // Draw the triangles
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        
        // Unbind the VAO
        glBindVertexArray(0);
    }
private:
    
};

#endif
