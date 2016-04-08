// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunShadowDirectionalLight.h"

#include "../Graphics/SunPrimitives.h"
#include "../Graphics/SunShader.h"

#include <glm/gtc/type_ptr.hpp>

SunShadowDirectionalLight::SunShadowDirectionalLight() {

}

SunShadowDirectionalLight::SunShadowDirectionalLight(glm::vec3 _color, glm::vec3 _direction) : SunDirectionalLight(_color, _direction) {

}

void SunShadowDirectionalLight::init() {
    addAction("shadowMap", &SunShadowDirectionalLight::shadowMap);
    addAction("update", &SunShadowDirectionalLight::update);
    addAction("uniform", &SunShadowDirectionalLight::uniform);

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

void SunShadowDirectionalLight::shadowMap(SunAction action) {
    SunShader *shader = action.getParameterPointer<SunShader>("shader");

    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glViewport(0, 0, resolution.x, resolution.y);

    clear();

    // Create the light-space matrix
	glm::mat4 projection = glm::ortho(-size.x, size.x, -size.y, size.y, nearPlane, farPlane);
	glm::mat4 view = glm::lookAt(center + (distance * glm::normalize(-direction)), center, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightMatrix = projection * view;

	glUniformMatrix4fv(shader->getUniformLocation("lightMatrix"), 1, GL_FALSE, glm::value_ptr(lightMatrix));

    SunAction render("render");
    render.setRecursive(true);
    render.addParameter("shader", shader);
    sendAction(render, target);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SunShadowDirectionalLight::update(SunAction action) {

}

void SunShadowDirectionalLight::uniform(SunAction action) {
    SunShader *shader = action.getParameterPointer<SunShader>("shader");
    int id = shader->getNextArrayIndex("shadowDirectionalLights");
    glUniform3f(shader->getUniformLocation("shadowDirectionalLights[" + std::to_string(id) + "].color"), color.r, color.g, color.b);

    glUniform3f(shader->getUniformLocation("shadowDirectionalLights[" + std::to_string(id) + "].direction"), direction.x, direction.y, direction.z);

    int textureUnit = shader->getNextTextureUnit();
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(shader->getUniformLocation("shadowDirectionalLights[" + std::to_string(id) + "].shadowMap"), textureUnit);

    glUniform1i(shader->getUniformLocation("shadowDirectionalLightCount"), shader->getArraySize("shadowDirectionalLights"));

    glm::mat4 projection = glm::ortho(-size.x, size.x, -size.y, size.y, nearPlane, farPlane);
	glm::mat4 view = glm::lookAt(center + (distance * glm::normalize(-direction)), center, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightMatrix = projection * view;

	glUniformMatrix4fv(shader->getUniformLocation("shadowDirectionalLights[" + std::to_string(id) + "].lightMatrix"), 1, GL_FALSE, glm::value_ptr(lightMatrix));
}
