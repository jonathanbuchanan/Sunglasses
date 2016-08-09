// Copyright 2016 Jonathan Buchanan.
// This file is part of glasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include <sunglasses/Extra/ShadowPointLight.h>

#include <sunglasses/Graphics/Primitives.h>
#include <sunglasses/Graphics/Shader.h>

#include <glm/gtc/type_ptr.hpp>

namespace sunglasses {

ShadowPointLight::ShadowPointLight() {

}

ShadowPointLight::ShadowPointLight(glm::vec3 _color, glm::vec3 _position) : PointLight(_color, _position) {

}

void ShadowPointLight::init() {
    addAction("shadowMap", &ShadowPointLight::shadowMap);
    addAction("action", &ShadowPointLight::update);
    addAction("uniform", &ShadowPointLight::uniform);

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

void ShadowPointLight::shadowMap(Action action) {
    Shader *shader = action.getParameterPointer<Shader>("shader");

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
        (*shader)["shadowMatrices[" + std::to_string(i) + "]"] = transforms[i];
    (*shader)["lightPosition"] = position;
    (*shader)["farPlane"] = farPlane;

    Action render("render");
    render.setRecursive(true);
    render.addParameter("shader", shader);
    sendAction(render, target);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowPointLight::update(Action action) {

}

void ShadowPointLight::uniform(Action action) {
    Shader *shader = action.getParameterPointer<Shader>("shader");
    int id = shader->getNextArrayIndex("shadowPointLights");

    (*shader)["shadowPointLights[" + std::to_string(id) + "].color"] = color;

    (*shader)["shadowPointLights[" + std::to_string(id) + "].position"] = position;

    (*shader)["shadowPointLights[" + std::to_string(id) + "].attenuate"] = true;

    (*shader)["shadowPointLights[" + std::to_string(id) + "].farPlane"] = farPlane;

    int textureUnit = shader->getNextTextureUnit();
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
    (*shader)["shadowPointLights[" + std::to_string(id) + "].shadowMap"] = textureUnit;

    (*shader)["shadowPointLightCount"] = shader->getArraySize("shadowPointLights");
}

} // namespace
