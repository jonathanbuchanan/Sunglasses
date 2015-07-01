//
//  SunCubemapObject.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/26/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunCubemapObject_h
#define OpenGL_Test_3_SunCubemapObject_h

#include "SunObject.h"
#include "SunModel.h"
#include "SunMesh.h"

#include "SOIL.h"

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLfloat cubemapVertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,
    
    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};

class SunCubemapMesh : public SunMesh {
public:
    GLuint textureID;
    
    SunCubemapMesh() {
        setUpGL();
    }
    
    SunCubemapMesh(vector<const GLchar *> _textures) {
        setUpGL();
        setUpTextures(_textures);
    }
    
    void setUpGL() {
        // Generate the VAO
        glGenVertexArrays(1, &VAO);
        
        // Generate the VBO
        glGenBuffers(1, &VBO);
        
        // Bind the VAO
        glBindVertexArray(VAO);
        
        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        
        // Initialize and write the data for the VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubemapVertices), &cubemapVertices, GL_STATIC_DRAW);
        
        // Initialize and set the vertex attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
        
        // Unbind the VBO
        glBindVertexArray(0);
    }
    
    void setUpTextures(vector<const GLchar *> _textures) {
        glDeleteTextures(1, &textureID);
        
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        
        int width, height;
        unsigned char *image;
        for (int i = 0; i < _textures.size(); ++i) {
            image = SOIL_load_image(_textures[i], &width, &height, 0, SOIL_LOAD_RGB);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
            SOIL_free_image_data(image);
        }
        
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    
    void render(SunShader _shader, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) {
        glUniform3f(glGetUniformLocation(_shader.program, "material.color"), .871, .353, .204);
        
        // Calculate the model matrix
        glm::mat4 modelMatrix;
        modelMatrix = glm::translate(modelMatrix, _position);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.x), glm::vec3(1.0, 0.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.y), glm::vec3(0.0, 1.0, 0.0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(_rotation.z), glm::vec3(0.0, 0.0, 1.0));
        modelMatrix = glm::scale(modelMatrix, _scale);
        
        // Pass the model matrix uniform
        glUniformMatrix4fv(glGetUniformLocation(_shader.program, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
        
        // Bind GL_TEXTURE_CUBE_MAP
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
        
        // Bind the VAO
        glBindVertexArray(VAO);
        
        // Draw the triangles
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // Unbind the VAO
        glBindVertexArray(0);
    }
    
private:
    
};

class SunCubemapObject : public SunObject {
public:
    SunCubemapMesh mesh;
    
    SunCubemapObject(int _tag) {
        tag = _tag;
        
        mesh = SunCubemapMesh();
    }
    
    void render(SunShader _shader, GLfloat _deltaTime, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale) {
        mesh.render(_shader, _position, _rotation, _scale);
        
        // Loop through the sub-objects and force them to render
        for (int i = 0; i < subObjects.size(); ++i) {
            subObjects[i]->render(_shader, _deltaTime);
        }
    }
    
private:
    
};

#endif
