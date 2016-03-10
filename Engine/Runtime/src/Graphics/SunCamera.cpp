// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunCamera.h"
#include <lua.hpp>

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
    script.registerObject(script["camera"]["position"], &position, "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);
    script.registerObject(script["camera"]["direction"], &direction, "x", &glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);

    script.registerObject("keyboard_manager", (SunKeyboardManager *)getService("keyboard_manager"), "pollKey", &SunKeyboardManager::keyDown);

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
    static glm::vec2 oldMouse;
    glm::vec2 offset = glm::vec2(mouse.x - oldMouse.x, oldMouse.y - mouse.y);
    oldMouse = mouse;

    const float sensitivity = 0.1f;
    offset *= sensitivity;
    yaw += offset.x;
    pitch += offset.y;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    float speed = 5.0f;
    float finalSpeed = speed * delta;
	SunKeyboardManager *keyboard = (SunKeyboardManager *)getService("keyboard_manager");
    if (keyboard->pollKey(GLFW_KEY_UP) == SunButtonStateDown)
        position += finalSpeed * direction;
    if (keyboard->pollKey(GLFW_KEY_DOWN) == SunButtonStateDown)
        position += finalSpeed * -direction;
    if (keyboard->pollKey(GLFW_KEY_RIGHT) == SunButtonStateDown)
        position += finalSpeed * glm::normalize(glm::cross(direction, cameraUp));
    if (keyboard->pollKey(GLFW_KEY_LEFT) == SunButtonStateDown)
        position += finalSpeed * -glm::normalize(glm::cross(direction, cameraUp));
    if (keyboard->pollKey(GLFW_KEY_SPACE) == SunButtonStateDown)
        position += finalSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
    if (keyboard->pollKey(GLFW_KEY_LEFT_SHIFT) == SunButtonStateDown)
        position += finalSpeed * -glm::vec3(0.0f, 1.0f, 0.0f);

    direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    direction.y = sin(glm::radians(pitch));
    direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

    script["update"](delta);
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

    // Check the type of projection
    matrix = glm::perspective(FOV, _aspectRatio, 0.01f, 100.0f);

    return matrix;
}

void SunCamera::passPerFrameUniforms(SunShader *_shader) {
    glUniform3f(_shader->getUniformLocation("viewPosition"), position.x, position.y, position.z);

    // Pass the view and projection matrices to the shader
    GLint viewMatrixLocation = _shader->getUniformLocation("view");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix()));

    GLint projectionMatrixLocation = _shader->getUniformLocation("projection");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix(800.0f / 600.0f)));
    GLint FOVlocation = _shader->getUniformLocation("camera.FOV");
    GLint nearPlaneLocation = _shader->getUniformLocation("camera.nearPlane");
    GLint farPlaneLocation = _shader->getUniformLocation("camera.farPlane");

    glUniform1f(FOVlocation, FOV);
    glUniform1f(nearPlaneLocation, 0.01f);
    glUniform1f(farPlaneLocation, 100.0f);
}
