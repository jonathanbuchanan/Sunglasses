// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunShadowPointLight.h"

#include "../Graphics/SunPrimitives.h"
#include "../Graphics/SunShader.h"

#include <glm/gtc/type_ptr.hpp>

SunShadowPointLight::SunShadowPointLight() {

}

SunShadowPointLight::SunShadowPointLight(glm::vec3 _color, glm::vec3 _position) : SunPointLight(_color, _position) {

}

void SunShadowPointLight::init() {
    addAction("shadowMap", &SunShadowPointLight::shadowMap);
    addAction("action", &SunShadowPointLight::update);
    addAction("uniform", &SunShadowPointLight::uniform);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    for (int i = 0; i < 6; ++i) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, resolution, resolution, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SunShadowPointLight::shadowMap(SunAction action) {
    SunShader *shader = action.getParameterPointer<SunShader>("shader");

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glViewport(0, 0, resolution, resolution);

    clear();

    glm::mat4 projection = glm::perspective(90.0f, 1.0f, nearPlane, farPlane); // FOV = 90 degrees, aspect ratio = resolution / resolution = 1

    glm::mat4 transforms[6];
    transforms[0] = projection * glm::lookAt(position, position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    transforms[1] = projection * glm::lookAt(position, position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    transforms[2] = projection * glm::lookAt(position, position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    transforms[3] = projection * glm::lookAt(position, position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
    transforms[4] = projection * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    transforms[5] = projection * glm::lookAt(position, position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));

    for (int i = 0; i < 6; ++i)
        glUniformMatrix4fv(shader->getUniformLocation("shadowMatrices[" + std::to_string(i) + "]"), 1, GL_FALSE, glm::value_ptr(transforms[i]));
    glUniform3f(shader->getUniformLocation("lightPosition"), position.x, position.y, position.z);
    glUniform1f(shader->getUniformLocation("farPlane"), farPlane);

    SunAction render("render");
    render.setRecursive(true);
    render.addParameter("shader", shader);
    sendAction(render, target);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SunShadowPointLight::update(SunAction action) {

}

void SunShadowPointLight::uniform(SunAction action) {
    SunShader *shader = action.getParameterPointer<SunShader>("shader");
    int id = shader->getNextArrayIndex("shadowPointLights");

    glUniform3f(shader->getUniformLocation("shadowPointLights[" + std::to_string(id) + "].color"), color.r, color.g, color.b);

    glUniform3f(shader->getUniformLocation("shadowPointLights[" + std::to_string(id) + "].position"), position.x, position.y, position.z);

    glUniform1i(shader->getUniformLocation("shadowPointLights[" + std::to_string(id) + "].attenuate"), true);

    glUniform1f(shader->getUniformLocation("shadowPointLights[" + std::to_string(id) + "].farPlane"), farPlane);

    int textureUnit = shader->getNextTextureUnit();
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    glUniform1i(shader->getUniformLocation("shadowPointLights[" + to_string(id) + "].shadowMap"), textureUnit);

    glUniform1i(shader->getUniformLocation("shadowPointLightCount"), shader->getArraySize("shadowPointLights"));
}
