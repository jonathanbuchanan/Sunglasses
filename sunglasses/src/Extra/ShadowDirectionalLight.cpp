// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extra/ShadowDirectionalLight.h>

#include <sunglasses/Graphics/Primitives.h>
#include <sunglasses/Graphics/Shader.h>

#include <glm/gtc/type_ptr.hpp>

namespace sunglasses {

ShadowDirectionalLight::ShadowDirectionalLight() {

}

ShadowDirectionalLight::ShadowDirectionalLight(glm::vec3 _color, glm::vec3 _direction) : DirectionalLight(_color, _direction) {

}

void ShadowDirectionalLight::init() {
    addAction("shadowMap", &ShadowDirectionalLight::shadowMap);
    addAction("update", &ShadowDirectionalLight::update);
    addAction("uniform", &ShadowDirectionalLight::uniform);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, resolution.x, resolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ShadowDirectionalLight::shadowMap(Action action) {
    Shader *shader = action.getParameterPointer<Shader>("shader");

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glViewport(0, 0, resolution.x, resolution.y);

    clear();

    // Create the light-space matrix
    glm::mat4 projection = glm::ortho(-size.x, size.x, -size.y, size.y, nearPlane, farPlane);
    glm::mat4 view = glm::lookAt(center + (distance * glm::normalize(-direction)), center, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightMatrix = projection * view;

    (*shader)["lightMatrix"] = lightMatrix;

    Action render("render");
    render.setRecursive(true);
    render.addParameter("shader", shader);
    sendAction(render, target);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowDirectionalLight::update(Action action) {

}

void ShadowDirectionalLight::uniform(Action action) {
    Shader *shader = action.getParameterPointer<Shader>("shader");
    int id = shader->getNextArrayIndex("shadowDirectionalLights");
    (*shader)["shadowDirectionlLights[" + std::to_string(id) + "].color"] = color;

    (*shader)["shadowDirectionalLights[" + std::to_string(id) + "].direction"] = direction;

    int textureUnit = shader->getNextTextureUnit();
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, texture);
    (*shader)["shadowDirectionalLights[" + std::to_string(id) + "].shadowMap"] = textureUnit;

    (*shader)["shadowDirectionalLightCount"] = shader->getArraySize("shadowDirectionalLights");

    glm::mat4 projection = glm::ortho(-size.x, size.x, -size.y, size.y, nearPlane, farPlane);
    glm::mat4 view = glm::lookAt(center + (distance * glm::normalize(-direction)), center, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightMatrix = projection * view;

    (*shader)["shadowDirectionalLights[" + std::to_string(id) + "].lightMatrix"] = lightMatrix;
}

} // namespace
