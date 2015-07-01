//
//  SunCamera.h
//  OpenGL_Test_3
//
//  Created by Jonathan Buchanan on 5/14/15.
//  Copyright (c) 2015 Virtual40. All rights reserved.
//

#ifndef OpenGL_Test_3_SunCamera_h
#define OpenGL_Test_3_SunCamera_h

#include <vector>
using namespace std;

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "SunButtonState.h"

class SunCamera {
public:
    // Position
    glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
    
    // Direction
    glm::vec3 cameraDirection = glm::vec3(1.0, 0.0, 0.0);
    
    // Up, Camera Right, and Camera Up
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, -cameraDirection));
    glm::vec3 cameraUp = glm::normalize(glm::cross(-cameraDirection, cameraRight));
    
    // Yaw and Pitch
    GLfloat yaw;
    GLfloat pitch;
    
    // Adjust the position of the camera for the given keys pressed, frame rate, and mouse/trackpad movement
    void doCameraMovement(map<int, SunButtonState> _keys, GLfloat _deltaTime, GLfloat _xOffset, GLfloat _yOffset) {
        // Calculate the movement speed
        GLfloat speed = 3.0 * _deltaTime;
        
        // Check for pressed keys and adjust position accordingly
        if (isPressed(_keys[GLFW_KEY_W])) {
            position += speed * cameraDirection;
        }
        if (isPressed(_keys[GLFW_KEY_S])) {
            position -= speed * cameraDirection;
        }
        if (isPressed(_keys[GLFW_KEY_D])) {
            position += speed * glm::normalize(glm::cross(cameraDirection, cameraUp));
        }
        if (isPressed(_keys[GLFW_KEY_A])) {
            position -= speed * glm::normalize(glm::cross(cameraDirection, cameraUp));
        }
        if (isPressed(_keys[GLFW_KEY_SPACE])) {
            position += speed * up;
        }
        if (isPressed(_keys[GLFW_KEY_LEFT_SHIFT])) {
            position -= speed * up;
        }
        
        // Adjust the yaw and pitch values based on the offset
        yaw += _xOffset;
        pitch += _yOffset;
        
        // Lock pitch in range of 89 to -89
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        
        // Calculate the new camera direciton based on the yaw and pitch
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraDirection = glm::normalize(front);
    }
    
    glm::mat4 viewMatrix() {
        // Recalculate the camera's right and the camera's up
        cameraRight = glm::normalize(glm::cross(up, -cameraDirection));
        cameraUp = glm::normalize(glm::cross(-cameraDirection, cameraRight));
        
        // Create the view matrix for the camera's position and direction
        glm::mat4 matrix = glm::lookAt(position, position + cameraDirection, cameraUp);
        return matrix;
    }
    
    glm::mat4 projectionMatrix(GLfloat _aspectRatio) {
        // Create the projection matrix for the given aspect ratio
        glm::mat4 matrix = glm::perspective(45.0f, _aspectRatio, 0.01f, 100.0f);
        return matrix;
    }
    
    void passPerFrameUniforms(SunShader _shader) {
        glUniform3f(glGetUniformLocation(_shader.program, "viewPosition"), position.x, position.y, position.z);
    }
    
    void setUpMatrixUniforms(SunShader _shader, GLfloat _aspectRatio) {
        // Pass the view and projection matrices to the shader
        GLint viewMatrixLocation = glGetUniformLocation(_shader.program, "view");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix()));
        
        GLint projectionMatrixLocation = glGetUniformLocation(_shader.program, "projection");
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix(_aspectRatio)));
    }
private:
    
};

#endif
