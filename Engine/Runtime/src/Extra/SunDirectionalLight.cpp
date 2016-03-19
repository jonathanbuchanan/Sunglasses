// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunDirectionalLight.h"

int SunDirectionalLight::lastId = 0;

SunDirectionalLight::SunDirectionalLight() {
    init();
}

SunDirectionalLight::SunDirectionalLight(glm::vec3 _color, glm::vec3 _direction) {
    color = _color;
    direction = _direction;

	init();
}

SunDirectionalLight::SunDirectionalLight(string _name) {
    setName(_name);

	init();
}

void SunDirectionalLight::init() {
	id = lastId;
	lastId++;

	addAction("uniform", &SunDirectionalLight::uniform);
	addAction("shadowMap", &SunDirectionalLight::shadowMap);
}

void SunDirectionalLight::uniform(SunAction action) {
    SunObject::uniform(action);
    SunShader *_shader = action.getParameterPointer<SunShader>("shader");
	glUniform1i(_shader->getUniformLocation(countUniform), lastId);
	/*int usedTextureUnits;
	if (action.parameterExists("usedTextureUnits"))
		usedTextureUnits = action.getParameter<int>("usedTextureUnits");*/

    glUniform3f(_shader->getUniformLocation(arrayUniform + "[" + std::to_string(id) + "].color"), color.r, color.g, color.b);

    glUniform3f(_shader->getUniformLocation(arrayUniform + "[" + std::to_string(id) + "].direction"), direction.x, direction.y, direction.z);

	glm::mat4 projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(-getDirection(), glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 lightMatrix = projection * view;

	glUniformMatrix4fv(glGetUniformLocation(_shader->getProgram(), "lightMatrix"), 1, GL_FALSE, glm::value_ptr(lightMatrix));
}

void SunDirectionalLight::shadowMap(SunAction action) {

}

void SunDirectionalLight::initializeShadowMap() {
	// Generate the framebuffer
	glGenFramebuffers(1, &shadowMapFramebuffer);

	// Generate the depthmap texture
	glGenTextures(1, &shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, shadowMapTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize.x, shadowMapSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Attach texture to the framebuffer

	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFramebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
