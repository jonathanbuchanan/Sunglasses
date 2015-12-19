#include "SunDirectionalLightObject.h"

SunDirectionalLightObject::SunDirectionalLightObject() {
    initializeDefaultPropertyAndFunctionMap();
}

SunDirectionalLightObject::SunDirectionalLightObject(glm::vec3 _color, glm::vec3 _direction) {
    color = _color;
    direction = _direction;
    
    initializeDefaultPropertyAndFunctionMap();
}

SunDirectionalLightObject::SunDirectionalLightObject(string _name) {
    setName(_name);

    initializeDefaultPropertyAndFunctionMap();
}

void SunDirectionalLightObject::initializeDefaultPropertyAndFunctionMap() {
    SunObject::initializeDefaultPropertyAndFunctionMap();
    
    addToFunctionMap("shadowMap", bind(&SunDirectionalLightObject::shadowMap, this, std::placeholders::_1));
    
    setType("light");
}

void SunDirectionalLightObject::passPerFrameUniforms(SunNodeSentAction _action) {
    SunObject::passPerFrameUniforms(_action);

    SunShader _shader = *(SunShader *) _action.parameters["shader"];

    // Set the uniforms for the directional light's diffuse and specular colors
    glUniform3f(_shader.getUniformLocation("directionalLight.color"), color.r, color.g, color.b);

    // Set the unifrom for the directional light's direction
    glUniform3f(_shader.getUniformLocation("directionalLight.direction"), direction.x, direction.y, direction.z);
}

void SunDirectionalLightObject::shadowMap(SunNodeSentAction _action) {
	
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
