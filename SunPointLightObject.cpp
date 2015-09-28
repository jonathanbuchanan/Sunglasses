#include "SunPointLightObject.h"

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

    setType("light");
}

void SunPointLightObject::passPerFrameUniforms(SunNodeSentAction _action) {
    SunObject::passPerFrameUniforms(_action);

    SunShader _shader = *(SunShader *)_action.parameters["shader"];
    
    // Set the uniforms for the point light's diffuse and specular colors
    glUniform3f(_shader.getUniformLocation("pointLights[" + std::to_string(pointLightID) + "].color"), color.r, color.g, color.b);

    // Set the uniform for the point light's position
    glUniform3f(_shader.getUniformLocation("pointLights[" + std::to_string(pointLightID) + "].position"), this->getPosition().x, this->getPosition().y, this->getPosition().z);

    // Set the uniforms for the point light's constant, linear, and quadratic terms
    glUniform1i(_shader.getUniformLocation("pointLights[" + std::to_string(pointLightID) + "].attenuate"), attenuate);
}

void SunPointLightObject::passPOVUniforms(SunShader _shader) {
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.01f, 100.0f);
    
    vector<glm::mat4> transforms;
    
    transforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    transforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    transforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    transforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    transforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    transforms.push_back(projection * glm::lookAt(this->getPosition(), this->getPosition() + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    
    for (int i = 0; i < 6; i++) {
        glUniformMatrix4fv(_shader.getUniformLocation("shadowMatrices[" + to_string(i) + "]"), 1, GL_FALSE, glm::value_ptr(transforms[i]));
    }
}