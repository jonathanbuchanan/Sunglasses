// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunPointLightObject.h"

#include <iostream>

SunPointLightObject::SunPointLightObject() {
    initializeDefaultPropertyAndFunctionMap();
}

SunPointLightObject::SunPointLightObject(glm::vec3 _color, glm::vec3 _position) {
    color = _color;
    this->setPosition(_position);
    
    initializeDefaultPropertyAndFunctionMap();
}

SunPointLightObject::SunPointLightObject(string _name) {
    setName(_name);

    initializeDefaultPropertyAndFunctionMap();
}

void SunPointLightObject::initializeDefaultPropertyAndFunctionMap() {
    SunObject::initializeDefaultPropertyAndFunctionMap();
	
	addToFunctionMap("shadowMap", bind(&SunPointLightObject::shadowMap, this, std::placeholders::_1));
	
    setType("light");
}

void SunPointLightObject::passPerFrameUniforms(SunNodeSentAction _action) {
    SunObject::passPerFrameUniforms(_action);

    SunShader _shader = *(SunShader *)_action.parameters["shader"];
	int usedTextureUnits;
	if (_action.parameters.find("usedTextureUnits") != _action.parameters.end())
		usedTextureUnits = *(int *)_action.parameters["usedTextureUnits"];
    
	if (shadows) {
		// Set the uniforms for the point light's color
    	glUniform3f(_shader.getUniformLocation("shadowPointLights[" + std::to_string(pointLightID) + "].color"), color.r, color.g, color.b);
		
   	 	// Set the uniform for the point light's position
   	 	glUniform3f(_shader.getUniformLocation("shadowPointLights[" + std::to_string(pointLightID) + "].position"), this->getPosition().x, this->getPosition().y, this->getPosition().z);
		
    	// Set the uniforms for the point light's constant, linear, and quadratic terms
    	glUniform1i(_shader.getUniformLocation("shadowPointLights[" + std::to_string(pointLightID) + "].attenuate"), attenuate);
		
		glActiveTexture(GL_TEXTURE1 + usedTextureUnits + pointLightID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMapTexture);
		glUniform1i(_shader.getUniformLocation("shadowPointLights[" + to_string(pointLightID) + "].shadowMap"), 1 + usedTextureUnits + pointLightID);
		glActiveTexture(GL_TEXTURE0);
	} else {
		// Set the uniforms for the point light's color
    	glUniform3f(_shader.getUniformLocation("pointLights[" + std::to_string(pointLightID) + "].color"), color.r, color.g, color.b);
		
   	 	// Set the uniform for the point light's position
   	 	glUniform3f(_shader.getUniformLocation("pointLights[" + std::to_string(pointLightID) + "].position"), this->getPosition().x, this->getPosition().y, this->getPosition().z);
		
    	// Set the uniforms for the point light's constant, linear, and quadratic terms
    	glUniform1i(_shader.getUniformLocation("pointLights[" + std::to_string(pointLightID) + "].attenuate"), attenuate);
	}
}

void SunPointLightObject::passPOVUniforms(SunShader _shader) {
	for (int i = 0; i < 6; i++)
		glUniformMatrix4fv(_shader.getUniformLocation("shadowMatrices[" + to_string(i) + "]"), 1, GL_FALSE, glm::value_ptr(lightTransforms[i]));
}

void SunPointLightObject::shadowMap(SunNodeSentAction _action) {
	SunNode *scene = (SunNode *)_action.parameters["scene"];
	
	glViewport(0, 0, 1024, 1024);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFramebuffer);
	clear();
	
	SunNodeSentAction renderAction;
	renderAction.action = "render";
	renderAction.parameters["deltaTime"] = _action.parameters["deltaTime"];
	
	string POVtype = "light";
	string POV = this->getName();
	
	renderAction.parameters["POVtype"] = &POVtype;
    renderAction.parameters["POV"] = &POV;
	renderAction.parameters["shaderMap"] = _action.parameters["shaderMap"];
	renderAction.parameters["uniforms"] = &_lightTransforms;
	
	sendAction(renderAction, scene);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	glViewport(0, 0, screenWidth, screenHeight);
}

void SunPointLightObject::initializeShadowMap() {
	glGenFramebuffers(1, &shadowMapFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFramebuffer);
	
	glGenTextures(1, &shadowMapTexture);
	
	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMapTexture);
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	for (GLuint i = 0; i < 6; i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);  
	
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMapTexture, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    	std::cout << "Frame buffer (" + this->getName() + ") not complete!" << std::endl;
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	// Create the light-space transforms
	
	GLfloat aspectRatio = 1.0f;
	GLfloat near = 0.01f;
	GLfloat far = 100.0f;
	
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspectRatio, near, far);
	
	lightTransforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    lightTransforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    lightTransforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    lightTransforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    lightTransforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    lightTransforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    
    for (int i = 0; i < 6; i++) {
    	SunShaderUniformObject uniform;
    	
    	uniform.setUniformName("shadowMatrices[" + to_string(i) + "]");
    	uniform.setType(SunShaderUniformObjectTypeMatrix4x4);
    	uniform.setValue(&lightTransforms[i]);
    	
    	_lightTransforms.push_back(uniform);
    }
    
    SunShaderUniformObject positionUniform;
    
    positionUniform.setUniformName("lightPosition");
    positionUniform.setType(SunShaderUniformObjectTypeVec3);
    positionUniform.setValue(&this->getPosition());
    
    _lightTransforms.push_back(positionUniform);
}