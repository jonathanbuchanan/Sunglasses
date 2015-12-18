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
	
}
