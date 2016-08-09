// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Graphics/SunCamera.h>

#include <sunglasses/Scripting/SunGlobalScriptingEnvironment.h>
#include <sunglasses/Graphics/SunShader.h>

namespace sunglasses {

template<> const std::string SunLuaTypeRegistrar<SunCamera>::typeName = "Camera";
template<> const std::map<std::string, SunScripting::SunLuaTypeDataMemberBase<SunCamera> *> SunLuaTypeRegistrar<SunCamera>::dataMembers = {
    {"yaw", new SunLuaTypeDataMember<float, SunCamera>("yaw", &SunCamera::yaw)},
    {"pitch", new SunLuaTypeDataMember<float, SunCamera>("pitch", &SunCamera::pitch)},
    {"position", new SunLuaComplexDataMember<glm::vec3, SunCamera>("position", &SunCamera::position)},
    {"direction", new SunLuaComplexDataMember<glm::vec3, SunCamera>("direction", &SunCamera::direction)},
    {"up", new SunLuaComplexDataMember<glm::vec3, SunCamera>("up", &SunCamera::cameraUp)}
};

SunCamera::SunCamera() {

}

SunCamera::SunCamera(GLfloat _FOV) {
    FOV = _FOV;
}

SunCamera::SunCamera(GLfloat _FOV, glm::vec3 _position) {
    FOV = _FOV;
    position = _position;
}

SunCamera::SunCamera(GLfloat _FOV, glm::vec3 _position, glm::vec3 _direction) {
    FOV = _FOV;
    position = _position;
    direction = _direction;
}

void SunCamera::init() {
    script.loadFile("../../Scripts/SunCamera.lua");
    script.registerType<glm::vec3>();
    
    script.registerObject(this, "camera");
    services.get<SunGlobalScriptingEnvironment>()->registerScript(this, script);

    setIgnoreTags(true);
    addAction("update", &SunCamera::update);
    addAction("uniform", &SunCamera::uniform);
}

void SunCamera::uniform(SunAction action) {
    passPerFrameUniforms(action.getParameterPointer<SunShader>("shader"));
}

void SunCamera::update(SunAction action) {
    double delta = services.get<SunWindowManager>()->getDelta();

    glm::vec2 mouse = services.get<SunCursorManager>()->getCursorPosition();

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
    glm::vec2 size = services.get<SunWindowManager>()->getSize();

    (*_shader)["viewPosition"] = position;

    // Pass the view and projection matrices to the shader
    (*_shader)["view"] = viewMatrix();

    (*_shader)["projection"] = projectionMatrix(size.x / size.y);

    (*_shader)["camera.FOV"] = FOV;
    (*_shader)["camera.nearPlane"] = 0.01f;
    (*_shader)["camera.farPlane"] = 100.0f;
}

} // namespace
