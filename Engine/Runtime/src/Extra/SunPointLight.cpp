// Copyright 2016 Jonathan Buchanan.
// This file is part of Sunglasses, which is licensed under the MIT License.
// See LICENSE.md for details.
#include "SunPointLight.h"

#include "../Graphics/SunWindowManager.h"

#include <glm/gtc/type_ptr.hpp>

int SunPointLight::lastId = 0;

SunPointLight::SunPointLight() {
    init();
}

SunPointLight::SunPointLight(glm::vec3 _color, glm::vec3 _position) {
    color = _color;
    this->setPosition(_position);

    init();
}

SunPointLight::SunPointLight(std::string _name) {
    setName(_name);

    init();
}

void SunPointLight::init() {
    id = lastId;
    lastId++;

    addAction("uniform", &SunPointLight::uniform);
    addAction("shadowMap", &SunPointLight::shadowMap);
}

void SunPointLight::uniform(SunAction action) {
    SunObject::uniform(action);
    SunShader *_shader = action.getParameterPointer<SunShader>("shader");
    glUniform1i(_shader->getUniformLocation(countUniform), lastId);
    /*int usedTextureUnits;
    if (action.parameterExists("usedTextureUnits"))
        usedTextureUnits = action.getParameter<int>("usedTextureUnits");*/

    if (shadows) {
        // Set the uniforms for the point light's color
        /*glUniform3f(_shader.getUniformLocation("shadowPointLights[" + std::to_string(pointLightID) + "].color"), color.r, color.g, color.b);

            // Set the uniform for the point light's position
            glUniform3f(_shader.getUniformLocation("shadowPointLights[" + std::to_string(pointLightID) + "].position"), this->getPosition().x, this->getPosition().y, this->getPosition().z);

        // Set the uniforms for the point light's constant, linear, and quadratic terms
        glUniform1i(_shader.getUniformLocation("shadowPointLights[" + std::to_string(pointLightID) + "].attenuate"), attenuate);

        glActiveTexture(GL_TEXTURE1 + usedTextureUnits + pointLightID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadowMapTexture);
        glUniform1i(_shader.getUniformLocation("shadowPointLights[" + to_string(pointLightID) + "].shadowMap"), 1 + usedTextureUnits + pointLightID);
        glActiveTexture(GL_TEXTURE0);*/
    } else {
        // Set the uniforms for the point light's color
        glUniform3f(_shader->getUniformLocation(arrayUniform + "[" + std::to_string(id) + "].color"), color.r, color.g, color.b);

            // Set the uniform for the point light's position
            glUniform3f(_shader->getUniformLocation(arrayUniform + "[" + std::to_string(id) + "].position"), this->getPosition().x, this->getPosition().y, this->getPosition().z);

        // Set the uniforms for the point light's constant, linear, and quadratic terms
        glUniform1i(_shader->getUniformLocation(arrayUniform + "[" + std::to_string(id) + "].attenuate"), attenuate);
    }
}

void SunPointLight::passPOVUniforms(SunShader _shader) {
    for (int i = 0; i < 6; i++)
        glUniformMatrix4fv(_shader.getUniformLocation("shadowMatrices[" + std::to_string(i) + "]"), 1, GL_FALSE, glm::value_ptr(lightTransforms[i]));
}

void SunPointLight::shadowMap(SunAction action) {
    SunNode *scene = action.getParameterPointer<SunNode>("scene");

    glViewport(0, 0, 1024, 1024);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFramebuffer);
    clear();

    SunAction renderAction("render");

    std::string POVtype = "light";
    std::string POV = this->getName();

    renderAction.addParameter("POVtype", &POVtype);
    renderAction.addParameter("POV", &POV);
    renderAction.addParameter("shaderMap", action.getParameter("shaderMap"));
    //renderAction.addParameter("uniforms", &_lightTransforms);

    sendAction(renderAction, scene);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glm::vec2 screen = ((SunWindowManager *)getService("window_manager"))->getSize();
    glViewport(0, 0, screen.x, screen.y);
}

void SunPointLight::initializeShadowMap() {
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
        /*SunShaderUniformObject uniform;

        uniform.setUniformName("shadowMatrices[" + to_string(i) + "]");
        uniform.setType(SunShaderUniformObjectTypeMatrix4x4);
        uniform.setValue(&lightTransforms[i]);

        _lightTransforms.push_back(uniform);*/
    }

    /*SunShaderUniformObject positionUniform;

    positionUniform.setUniformName("lightPosition");
    positionUniform.setType(SunShaderUniformObjectTypeVec3);
    positionUniform.setValue(&this->getPosition());

    _lightTransforms.push_back(positionUniform);*/
}
