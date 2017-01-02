// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/Camera.h>

#include <sunglasses/Scripting/GlobalScriptingEnvironment.h>
#include <sunglasses/Graphics/Shader.h>

namespace sunglasses {

namespace graphics {

template<> const std::string LuaTypeRegistrar<Camera>::typeName = "Camera";
template<> const std::map<std::string, Scripting::LuaTypeDataMemberBase<Camera> *> LuaTypeRegistrar<Camera>::dataMembers = {
    {"yaw", new LuaTypeDataMember<float, graphics::Camera>("yaw", &graphics::Camera::yaw)},
    {"pitch", new LuaTypeDataMember<float, graphics::Camera>("pitch", &graphics::Camera::pitch)},
    {"position", new LuaComplexDataMember<glm::vec3, graphics::Camera>("position", &graphics::Camera::position)},
    {"direction", new LuaComplexDataMember<glm::vec3, graphics::Camera>("direction", &graphics::Camera::direction)},
    {"up", new LuaComplexDataMember<glm::vec3, graphics::Camera>("up", &graphics::Camera::cameraUp)}
};

Camera::Camera() {

}

Camera::Camera(GLfloat _FOV) {
    FOV = _FOV;
}

Camera::Camera(GLfloat _FOV, glm::vec3 _position) {
    FOV = _FOV;
    position = _position;
}

Camera::Camera(GLfloat _FOV, glm::vec3 _position, glm::vec3 _direction) {
    FOV = _FOV;
    position = _position;
    direction = _direction;
}

void Camera::init() {
    script.loadFile("../../Scripts/Camera.lua");
    script.registerType<glm::vec3>();

    script.registerObject(this, "camera");
    services.get<GlobalScriptingEnvironment>()->registerScript(this, script);

    setIgnoreTags(true);
    addAction("update", &Camera::update);
    addAction("uniform", &Camera::uniform);
}

void Camera::uniform(Action action) {
    passPerFrameUniforms(action.getParameterPointer<Shader>("shader"));
}

void Camera::update(Action action) {
    double delta = services.get<WindowManager>()->getDelta();

    glm::vec2 mouse = services.get<CursorManager>()->getCursorPosition();

    script["update"](delta, mouse.x, mouse.y);
}

glm::mat4 Camera::viewMatrix() {
    // Recalculate the camera's right and the camera's up
    cameraRight = glm::normalize(glm::cross(up, direction));
    cameraUp = glm::normalize(glm::cross(direction, cameraRight));

    // Create the view matrix for the camera's position and direction
    glm::mat4 matrix = glm::lookAt(position, position + direction, cameraUp);
    return matrix;
}

glm::mat4 Camera::projectionMatrix(GLfloat _aspectRatio) {
    // Create the projection matrix
    glm::mat4 matrix;

    matrix = glm::perspective(glm::radians(FOV), _aspectRatio, 0.01f, 100.0f);

    return matrix;
}

void Camera::passPerFrameUniforms(Shader *_shader) {
    glm::vec2 size = services.get<WindowManager>()->getSize();

    (*_shader)["viewPosition"] = position;

    // Pass the view and projection matrices to the shader
    (*_shader)["view"] = viewMatrix();

    (*_shader)["projection"] = projectionMatrix(size.x / size.y);

    (*_shader)["camera.FOV"] = FOV;
    (*_shader)["camera.nearPlane"] = 0.01f;
    (*_shader)["camera.farPlane"] = 100.0f;
}

} // namespace
} // namespace
