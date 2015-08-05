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

#include "../Libraries/glm/glm.hpp"
#include "../Libraries/glm/gtc/matrix_transform.hpp"

#include "../Utility.h"

#include "../SunButtonState.h"

// Definition of SunCameraProjectionType
enum SunCameraProjectionType {
    SunCameraProjectionTypePerspective = 0,
    SunCameraProjectionTypeOrthographic
};

class SunCamera {
public:
    // Position
    glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
    
    // Direction
    glm::vec3 direction = glm::vec3(0.0, 0.0, 1.0);
    
    // Up, Camera Right, and Camera Up
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, -direction));
    glm::vec3 cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
    
    // Yaw and Pitch
    GLfloat yaw = 0.0f;
    GLfloat pitch = 0.0f;
    
    // Projection Type
    SunCameraProjectionType projection;
    
    // FOV (in degrees)
    GLfloat FOV = 45.0f;
    
    // Width and height
    GLfloat width = 10.0f;
    GLfloat height = 10.0f;
    
    SunCamera() {
        
    }
    
    SunCamera(SunCameraProjectionType _projection, GLfloat _FOV) {
        projection = _projection;
        FOV = _FOV;
    }
    
    SunCamera(SunCameraProjectionType _projection, GLfloat _FOV, glm::vec3 _position) {
        projection = _projection;
        FOV = _FOV;
        position = _position;
    }
    
    SunCamera(SunCameraProjectionType _projection, GLfloat _FOV, GLfloat _yaw, GLfloat _pitch) {
        projection = _projection;
        FOV = _FOV;
        yaw = _yaw;
        pitch = _pitch;
    }
    
    SunCamera(SunCameraProjectionType _projection, GLfloat _FOV, glm::vec3 _position, GLfloat _yaw, GLfloat _pitch) {
        projection = _projection;
        FOV = _FOV;
        position = _position;
        yaw = _yaw;
        pitch = _pitch;
    }
    
    SunCamera(SunCameraProjectionType _projection, GLfloat _FOV, GLfloat _width, GLfloat _height, GLfloat _yaw, GLfloat _pitch) {
        projection = _projection;
        FOV = _FOV;
        width = _width;
        height = _height;
        yaw = _yaw;
        pitch = _pitch;
    }
    
    // Adjust the position of the camera for the given keys pressed, frame rate, and mouse/trackpad movement
    void doCameraMovement(map<int, SunButtonState> _keys, GLfloat _deltaTime, GLfloat _xOffset, GLfloat _yOffset) {
        // Calculate the movement speed
        GLfloat speed = 3.0 * _deltaTime;
        
        // Check for pressed keys and adjust position accordingly
        if (isPressed(_keys[GLFW_KEY_W])) {
            position += speed * direction;
        }
        if (isPressed(_keys[GLFW_KEY_S])) {
            position -= speed * direction;
        }
        if (isPressed(_keys[GLFW_KEY_D])) {
            position += speed * glm::normalize(glm::cross(direction, cameraUp));
        }
        if (isPressed(_keys[GLFW_KEY_A])) {
            position -= speed * glm::normalize(glm::cross(direction, cameraUp));
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
        direction = glm::normalize(front);
    }
    
    glm::mat4 viewMatrix() {
        // Recalculate the camera's right and the camera's up
        cameraRight = glm::normalize(glm::cross(up, -direction));
        cameraUp = glm::normalize(glm::cross(-direction, cameraRight));
        
        // Create the view matrix for the camera's position and direction
        glm::mat4 matrix = glm::lookAt(position, position + direction, cameraUp);
        return matrix;
    }
    
    glm::mat4 projectionMatrix(GLfloat _aspectRatio) {
        // Create the projection matrix
        glm::mat4 matrix;
        
        // Check the type of projection
        if (projection == SunCameraProjectionTypePerspective)
            matrix = glm::perspective(FOV, _aspectRatio, 0.01f, 100.0f);
        else if (projection == SunCameraProjectionTypeOrthographic)
            matrix = glm::ortho(-((width * _aspectRatio) / 2.0f), (width * _aspectRatio) / 2.0f, -(height / 2.0f), (height / 2.0f), 0.1f, 100.0f);
        
        return matrix;
    }
    
    void passPerFrameUniforms(SunShader _shader) {
        glUniform3f(glGetUniformLocation(_shader.program, "viewPosition"), position.x, position.y, position.z);
        
        // Pass the view and projection matrices to the shader
        GLint viewMatrixLocation = glGetUniformLocation(_shader.program, "view");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix()));
        
        GLint projectionMatrixLocation = glGetUniformLocation(_shader.program, "projection");
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix(800.0f / 600.0f)));
        
        GLint FOVlocation = glGetUniformLocation(_shader.program, "camera.FOV");
        GLint nearPlaneLocation = glGetUniformLocation(_shader.program, "camera.nearPlane");
        GLint farPlaneLocation = glGetUniformLocation(_shader.program, "camera.farPlane");
        
        glUniform1f(FOVlocation, FOV);
        glUniform1f(nearPlaneLocation, 0.01f);
        glUniform1f(farPlaneLocation, 100.0f);
    }
    
private:
    
};

#endif
