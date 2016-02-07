// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunCamera.h"

SunCamera::SunCamera() { }

SunCamera::SunCamera(SunCameraProjectionType _projection, GLfloat _FOV) {
    projection = _projection;
    FOV = _FOV;
}

SunCamera::SunCamera(SunCameraProjectionType _projection, GLfloat _FOV, glm::vec3 _position) {
    projection = _projection;
    FOV = _FOV;
    position = _position;
}

SunCamera::SunCamera(SunCameraProjectionType _projection, GLfloat _FOV, GLfloat _yaw, GLfloat _pitch) {
    projection = _projection;
    FOV = _FOV;
    yaw = _yaw;
    pitch = _pitch;
}

SunCamera::SunCamera(SunCameraProjectionType _projection, GLfloat _FOV, glm::vec3 _position, GLfloat _yaw, GLfloat _pitch) {
    projection = _projection;
    FOV = _FOV;
    position = _position;
    yaw = _yaw;
    pitch = _pitch;
}

SunCamera::SunCamera(SunCameraProjectionType _projection, GLfloat _FOV, GLfloat _width, GLfloat _height, GLfloat _yaw, GLfloat _pitch) {
    projection = _projection;
    FOV = _FOV;
    width = _width;
    height = _height;
    yaw = _yaw;
    pitch = _pitch;
}

void SunCamera::doCameraMovement(map<int,SunButtonState> _keys, GLfloat _deltaTime, GLfloat _xOffset, GLfloat _yOffset) {
    // Calculate the movement speed
    /*GLfloat speed = 3.0 * _deltaTime;

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
    direction = glm::normalize(front);*/
}

glm::mat4 SunCamera::viewMatrix() {
    // Recalculate the camera's right and the camera's up
    cameraRight = glm::normalize(glm::cross(up, -direction));
    cameraUp = glm::normalize(glm::cross(-direction, cameraRight));

    // Create the view matrix for the camera's position and direction
    glm::mat4 matrix = glm::lookAt(position, position + direction, cameraUp);
    return matrix;
}

glm::mat4 SunCamera::projectionMatrix(GLfloat _aspectRatio) {
    // Create the projection matrix
    glm::mat4 matrix;

    // Check the type of projection
    if (projection == SunCameraProjectionTypePerspective)
        matrix = glm::perspective(FOV, _aspectRatio, 0.01f, 100.0f);
    else if (projection == SunCameraProjectionTypeOrthographic)
        matrix = glm::ortho(-((width * _aspectRatio) / 2.0f), (width * _aspectRatio) / 2.0f, -(height / 2.0f), (height / 2.0f), 0.1f, 100.0f);

    return matrix;
}

void SunCamera::passPerFrameUniforms(SunShader _shader) {
    glUniform3f(_shader.getUniformLocation("viewPosition"), position.x, position.y, position.z);
    
    // Pass the view and projection matrices to the shader
    GLint viewMatrixLocation = _shader.getUniformLocation("view");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix()));

    GLint projectionMatrixLocation = _shader.getUniformLocation("projection");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix(800.0f / 600.0f)));

    GLint FOVlocation = _shader.getUniformLocation("camera.FOV");
    GLint nearPlaneLocation = _shader.getUniformLocation("camera.nearPlane");
    GLint farPlaneLocation = _shader.getUniformLocation("camera.farPlane");

    glUniform1f(FOVlocation, FOV);
    glUniform1f(nearPlaneLocation, 0.01f);
    glUniform1f(farPlaneLocation, 100.0f);
}

