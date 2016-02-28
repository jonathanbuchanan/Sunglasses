// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.

#ifndef OpenGL_Test_3_SunCamera_h
#define OpenGL_Test_3_SunCamera_h

#include <vector>
using namespace std;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/SunNode.h"
#include "../Core/SunScriptedNode.h"
#include "../Core/Utility.h"
#include "SunWindowManager.h"
#include "../Input/SunKeyboardManager.h"
#include "../Input/SunCursorManager.h"

#include <GLFW/glfw3.h>

class SunCamera : public SunScriptedNode {
public:
    SunCamera();
    SunCamera(GLfloat _FOV);
    SunCamera(GLfloat _FOV, glm::vec3 _position);
    SunCamera(GLfloat _FOV, glm::vec3 _position, glm::vec3 _direction);

    virtual void init();
    virtual void uniform(SunAction action);
    void update(SunAction action);

    glm::mat4 viewMatrix();
    glm::mat4 projectionMatrix(GLfloat _aspectRatio);
    void passPerFrameUniforms(SunShader *_shader);

    inline glm::vec3 & getPosition() { return position; }
    inline void setPosition(glm::vec3 _position) { position = _position; }

    inline glm::vec3 & getDirection() { return direction; }
    inline void setDirection(glm::vec3 _direction) { direction = _direction; }

    inline glm::vec3 & getUp() { return up; }
    inline glm::vec3 & getCameraRight() { return cameraRight; }
    inline glm::vec3 & getCameraUp() { return cameraUp; }

    inline GLfloat & getYaw() { return yaw; }
    inline GLfloat & getPitch() { return pitch; }

    inline GLfloat & getFOV() { return FOV; }
    inline void setFOV(GLfloat _FOV) { FOV = _FOV; }

    inline GLfloat & getWidth() { return width; }
    inline GLfloat & getHeight() { return height; }
    inline void setWidth(GLfloat _width) { width = _width; }
    inline void setHeight(GLfloat _height) { height = _height; }
private:
    // Position
    glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);

    // Direction
    glm::vec3 direction = glm::vec3(0.0, 0.0, 1.0);

    // Up, Camera Right, and Camera Up
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, direction));
    glm::vec3 cameraUp = glm::normalize(glm::cross(direction, cameraRight));

    // Yaw and Pitch
    GLfloat yaw = 0.0f;
    GLfloat pitch = 0.0f;

    // FOV (in degrees)
    GLfloat FOV = 45.0f;

    // Width and height
    GLfloat width = 10.0f;
    GLfloat height = 10.0f;
};

#endif
