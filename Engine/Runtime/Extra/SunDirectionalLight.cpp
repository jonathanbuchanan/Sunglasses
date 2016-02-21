// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunDirectionalLight.h"

SunDirectionalLightObject::SunDirectionalLightObject() {
    
}

SunDirectionalLightObject::SunDirectionalLightObject(glm::vec3 _color, glm::vec3 _direction) {
    color = _color;
    direction = _direction; 
}

SunDirectionalLightObject::SunDirectionalLightObject(string _name) {
    setName(_name); 
}

void SunDirectionalLightObject::init() { 
	addAction("shadowMap", &SunDirectionalLightObject::shadowMap); 
    
    //setType("light");
}

void SunDirectionalLightObject::passPerFrameUniforms(SunAction action) {
    SunObject::uniform(action);
    
    SunShader _shader = *(SunShader *)action.getParameter("shader");
	int usedTextureUnits;
	if (action.parameterExists("usedTextureUnits"))
		usedTextureUnits = *(int *)action.getParameter("usedTextureUnits");
	
    glUniform3f(_shader.getUniformLocation("directionalLights[" + std::to_string(directionalLightID) + "].color"), color.r, color.g, color.b);
    
    glUniform3f(_shader.getUniformLocation("directionalLights[" + std::to_string(directionalLightID) + "].direction"), direction.x, direction.y, direction.z);
}

void SunDirectionalLightObject::shadowMap(SunAction action) {
	
}

void SunDirectionalLightObject::initializeShadowMap() {
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
