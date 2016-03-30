// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunCamera.h"


#include "../Logic/SunGlobalLogicEnvironment.h"
#include "SunShader.h"

SunCamera::SunCamera() {

}

SunCamera::SunCamera(GLfloat _FOV) {
    SunCamera();
    FOV = _FOV;
}

SunCamera::SunCamera(GLfloat _FOV, glm::vec3 _position) {
    SunCamera();
    FOV = _FOV;
    position = _position;
}

SunCamera::SunCamera(GLfloat _FOV, glm::vec3 _position, glm::vec3 _direction) {
    SunCamera();
    FOV = _FOV;
    position = _position;
    direction = _direction;
}

void SunCamera::init() {
    script.loadFile("../../Engine/Scripts/SunCamera.lua");

    script.registerObject("camera", this, "yaw", &SunCamera::yaw, "pitch", &SunCamera::pitch, "FOV", &SunCamera::FOV);
    script.registerType<glm::vec3>("vec3", "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);
    script.registerObjectAsType(script["camera"]["position"], "vec3", &position);
    script.registerObjectAsType(script["camera"]["direction"], "vec3", &direction);
    script.registerObjectAsType(script["camera"]["up"], "vec3", &cameraUp);

    script.registerObject("window_manager", (SunWindowManager *)getService("window_manager"), "getDelta", &SunWindowManager::getDelta);
    script.registerObject("keyboard_manager", (SunKeyboardManager *)getService("keyboard_manager"), "pollKey", &SunKeyboardManager::keyDown);
    ((SunGlobalLogicEnvironment *)getService("global_logic_environment"))->registerWithScript(script);

    setIgnoreTags(true);
    addAction("update", &SunCamera::update);
    addAction("uniform", &SunCamera::uniform);
}

void SunCamera::uniform(SunAction action) {
    passPerFrameUniforms(action.getParameterPointer<SunShader>("shader"));
}

void SunCamera::update(SunAction action) {
    double delta = ((SunWindowManager *)getService("window_manager"))->getDelta();

    glm::vec2 mouse = ((SunCursorManager *)getService("cursor_manager"))->getCursorPosition();

    script["update"](delta, mouse.x, mouse.y);
}

glm::mat4 SunCamera::viewMatrix() {
    // Recalculate the camera's right and the camera's up
    cameraRight = glm::normalize(glm::cross(up, direction));
    cameraUp = glm::normalize(glm::cross(direction, cameraRight));

    // Create the view matrix for the camera's position and direction
    glm::mat4 matrix = glm::lookAt(position, position + direction, cameraUp);
    return matrix;
}

glm::mat4 SunCamera::projectionMatrix(GLfloat _aspectRatio) {
    // Create the projection matrix
    glm::mat4 matrix;

    matrix = glm::perspective(glm::radians(FOV), _aspectRatio, 0.01f, 100.0f);

    return matrix;
}

void SunCamera::passPerFrameUniforms(SunShader *_shader) {
    glUniform3f(_shader->getUniformLocation("viewPosition"), position.x, position.y, position.z);

    // Pass the view and projection matrices to the shader
    GLint viewMatrixLocation = _shader->getUniformLocation("view");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix()));

    GLint projectionMatrixLocation = _shader->getUniformLocation("projection");

    glm::vec2 size = ((SunWindowManager *)getService("window_manager"))->getSize();

    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix(size.x / size.y)));
    GLint FOVlocation = _shader->getUniformLocation("camera.FOV");
    GLint nearPlaneLocation = _shader->getUniformLocation("camera.nearPlane");
    GLint farPlaneLocation = _shader->getUniformLocation("camera.farPlane");

    glUniform1f(FOVlocation, FOV);
    glUniform1f(nearPlaneLocation, 0.01f);
    glUniform1f(farPlaneLocation, 100.0f);
}
